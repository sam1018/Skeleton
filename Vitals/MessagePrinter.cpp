#include "MessagePrinter.h"
#include "UI\IOutputWindow.h"
#include "Vitals\IVitalsInterfaceManager.h"
#include <mutex>
#include <vector>
#include <atomic>
#include <thread>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <boost\circular_buffer.hpp>


using namespace UI;
using namespace VT;
using namespace std;
using namespace boost;



template< class Elem = char, class Tr = std::char_traits< Elem > >
class StdRedirector : public std::basic_streambuf< Elem, Tr >
{
public:
	StdRedirector(std::ostream &a_Stream, MsgCatID wnd) :
		m_Stream{ a_Stream },
		m_pBuf{ m_Stream.rdbuf(this) },
		outWndId{ wnd },
		mp{ GetMessagePrinter() }
	{
	}

	~StdRedirector()
	{
		m_Stream.rdbuf(m_pBuf);
	}

	std::streamsize xsputn(const Elem *_Ptr, std::streamsize _Count)
	{
		mp->PrintMessage(outWndId, _Ptr, true, true);
		return _Count;
	}

	typename Tr::int_type overflow(typename Tr::int_type v)
	{
		std::string s;
		s += Tr::to_char_type(v);
		mp->PrintMessage(outWndId, s, true, true);
		return Tr::not_eof(v);
	}

	void Pause()
	{
		m_Stream.rdbuf(m_pBuf);
	}

	void Resume()
	{
		m_Stream.rdbuf(this);
	}

private:
	std::basic_ostream<Elem, Tr> &m_Stream;
	std::streambuf *m_pBuf;
	MsgCatID outWndId;
	IMessagePrinter *mp;
};



class RedirHandler : public IRedirHandler
{
public:
	RedirHandler(std::ostream &a_Stream, MsgCatID wnd) :
		redir{ a_Stream, wnd }
	{}

	virtual ~RedirHandler()
	{
	}

private:
	virtual void Pause_()
	{
		redir.Pause();
	}

	virtual void Resume_()
	{
		redir.Resume();
	}

private:
	StdRedirector<> redir;
};


class CircularString
{
public:
	explicit CircularString(int bufferSize) :
		text{ bufferSize }
	{
	}

	operator string() const
	{
		return string{ text.begin(), text.end() };
	}

	void Clear()
	{
		text.clear();
	}

	void Append(const std::string &str)
	{
		for (auto &c : str)
			text.push_back(c);
	}

private:
	circular_buffer<char> text;
};

ostream& operator<<(ostream &os, const CircularString &cs)
{
	os << (string)cs;
	return os;
}


class MessagePrinter::MessagePrinterImpl
{
	struct Category
	{
		MsgCatID id;
		string categoryName;
		CircularString text;

		Category(MsgCatID catId, const string &categoryName, int bufferSize) :
			id{ catId },
			categoryName{ categoryName },
			text{ bufferSize }
		{
		}
	};

	using Categories = vector<Category>;
	using CategoryIter = Categories::iterator;

	CategoryIter GetCategoryByName(const string &categoryName)
	{
		return find_if(categories.begin(), categories.end(),
			[categoryName](auto &item) { return item.categoryName == categoryName; });
	}

	CategoryIter GetCategoryByID(MsgCatID id)
	{
		return find_if(categories.begin(), categories.end(),
			[id](auto &item) { return item.id == id; });
	}

	void ComboCategoryChanged(const std::string &cat)
	{
		auto iter = GetCategoryByName(cat);
		PrintMessage(iter->id, iter->text, 
			false, true, __FILE__, __LINE__);
	}

	void Runner()
	{
		while (keepGoing)
		{
			if (needPrinting)
			{
				lock_guard<mutex> lock(m);
				if (outputWindow)
					outputWindow->Refresh(print->categoryName, print->text);
				else
					cout << print->text << "\n";

				needPrinting = false;
			}

			this_thread::sleep_for(static_cast<chrono::milliseconds>(printerThreadSleepTime));
		}
	}

public:
	MessagePrinterImpl()
	{
		categories.reserve(totalCategories);
	}

	~MessagePrinterImpl()
	{
		keepGoing = false;
		printerThread.join();
		lock_guard<mutex> lock(m);
	}

	void SetOutputWindow(IOutputWindow *param)
	{
		outputWindow = param;

		if (outputWindow)
		{		
			// Vitals leave longer than UI... so no worries regarding lifetime
			outputWindow->SetComboCategoryChangedCallback([this](const std::string &cat) {ComboCategoryChanged(cat); });

			if (outputWindow)
			{
				for (auto &item : categories)
					outputWindow->AddCategory(item.categoryName);
			}
		}
	}

	MsgCatID RegisterOutputWindowCategory(const string &categoryName)
	{
		if (!keepGoing)
			return -1;

		lock_guard<mutex> lock(m);

		auto iter = GetCategoryByName(categoryName);

		MsgCatID ret = nextId;
		if (iter == categories.end())
		{
			assert(nextId != totalCategories);

			categories.push_back(Category{ nextId++, categoryName, settings.bufferSize });

			if (outputWindow)
			{
				// This function may get called outside of main thread
				// QT Plugin needs to make sure this situation is properly handled
				// Because, in QT this is not acceptable to send event to an object outside of GUI thread
				outputWindow->AddCategory(categoryName);
			}
		}
		else
			ret = iter->id;

		return ret;
	}

	std::string FormatMsg(const string &text, const char *file, int line)
	{
		using namespace std::literals::string_literals;

		string res;
		if (settings.showFileName)
			res += ("<File="s + file + ">"s);
		if (settings.showLineNumber)
			res += ("<Line="s + to_string(line) + ">"s);
		res += text;
		if (settings.appendNewLine)
			res += "\n"s;

		return res;
	}

	void PrintMessage(MsgCatID id, const string &text, bool append,
		bool makeCurrrentCategory, const char *file, int line)
	{
		if (!keepGoing)
			return;

		lock_guard<mutex> lock(m);

		auto iter = GetCategoryByID(id);

		assert(iter != categories.end());

		string msg = FormatMsg(text, file, line);

		if(!append)
			iter->text.Clear();

		iter->text.Append(msg);

		if (makeCurrrentCategory)
		{
			needPrinting = true;
			print = iter;
		}
	}

	std::unique_ptr<IRedirHandler> RedirectStream(std::ostream &stream, MsgCatID cat)
	{
		return make_unique<RedirHandler>(stream, cat);
	}

	void StartPrinterThread()
	{
		printerThread = thread([this]() { Runner(); });
	}

private:
	MsgCatID nextId = 0;
	IOutputWindow *outputWindow = nullptr;
	mutex m;
	MessagePrinterSettings settings;
	thread printerThread;
	atomic<bool> keepGoing = true;
	atomic<bool> needPrinting = false;
	const int printerThreadSleepTime = 100 / settings.refreshRate;
	const int totalCategories = settings.totalCategories;
	Categories categories;
	CategoryIter print;
};



MessagePrinter::MessagePrinter() :
	messagePrinterImpl{ make_unique<MessagePrinterImpl>() }
{
	MsgCat_PluginExplorer = RegisterMessageCategory("Plugin Explorer");
	MsgCat_ErrorMsg = RegisterMessageCategory("Error Message");
}

MessagePrinter::~MessagePrinter()
{
}

MsgCatID MessagePrinter::RegisterMessageCategory_(const string &categoryName)
{
	return messagePrinterImpl->RegisterOutputWindowCategory(categoryName);
}

void MessagePrinter::PrintMessage_(MsgCatID id, const string &text, bool append,
	bool makeCurrrentCategory, const char *file, int line)
{
	messagePrinterImpl->PrintMessage(id, text, append, makeCurrrentCategory, file, line);
}

void MessagePrinter::SetOutputWindow_(IOutputWindow * wnd)
{
	messagePrinterImpl->SetOutputWindow(wnd);
}

std::unique_ptr<IRedirHandler> MessagePrinter::RedirectStream_(std::ostream &stream, MsgCatID cat)
{
	return messagePrinterImpl->RedirectStream(stream, cat);
}

void MessagePrinter::StartPrinterThread_()
{
	messagePrinterImpl->StartPrinterThread();
}
