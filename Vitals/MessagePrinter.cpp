#include "MessagePrinter.h"
#include "UI\IOutputWindow.h"
#include "Vitals\IVitalsInterfaceManager.h"
#include <vector>
#include <algorithm>
#include <mutex>
#include <iostream>
#include <sstream>


using namespace UI;
using namespace VT;
using namespace std;



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


class MessagePrinter::MessagePrinterImpl
{
	struct Category
	{
		MsgCatID id;
		string categoryName;
		string text;
	};

	using Categories = vector<Category>;
	using CategoryIter = vector<Category>::iterator;

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

	void ThrowIfItemNotFound(CategoryIter iter, const string &item)
	{
		if (iter == categories.end())
			throw runtime_error((item + ": No such output window category.").c_str());
	}

	void ComboCategoryChanged(const std::string &cat)
	{
		auto iter = GetCategoryByName(cat);
		PrintMessage(iter->id, iter->text, false, true, __FILE__, __LINE__);
	}

public:
	void SetOutputWindow(IOutputWindow *param)
	{
		outputWindow = param;

		// Vitals leave longer than UI... so no worries regarding lifetime
		outputWindow->SetComboCategoryChangedCallback([this](const std::string &cat) {ComboCategoryChanged(cat); });

		if (outputWindow)
		{
			for (auto &item : categories)
				outputWindow->AddCategory(item.categoryName);
		}
	}

	MsgCatID RegisterOutputWindowCategory(const string &categoryName)
	{
		lock_guard<mutex> lock(m);

		auto iter = GetCategoryByName(categoryName);

		MsgCatID ret = nextId;
		if (iter == categories.end())
		{
			categories.push_back(Category{ nextId++, categoryName, "" });

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
		stringstream ss;
		if (settings.showFileName)
			ss << "<File=" << file << ">";
		if (settings.showLineNumber)
			ss << "<Line=" << line << ">";
		ss << text;
		if (settings.appendNewLine)
			ss << "\n";

		return ss.str();
	}

	void PrintMessage(MsgCatID id, const string &text, bool append,
		bool makeCurrrentCategory, const char *file, int line)
	{
		lock_guard<mutex> lock(m);

		auto iter = GetCategoryByID(id);

		ThrowIfItemNotFound(iter, to_string(id));

		string msg = FormatMsg(text, file, line);

		if (append)
			iter->text += msg;
		else
			iter->text = msg;

		if (makeCurrrentCategory)
		{
			if (outputWindow)
			{
				// This function may get called outside of main thread
				// QT Plugin needs to make sure this situation is properly handled
				// Because, in QT this is not acceptable to send event to an object outside of GUI thread
				outputWindow->Refresh(iter->categoryName, iter->text);
			}
			else
			{
				// User wants to print something, but outputWindow is not yet ready
				// So print it in cout
				cout << iter->text << "\n";
			}
		}
	}

	std::unique_ptr<IRedirHandler> RedirectStream(std::ostream &stream, MsgCatID cat)
	{
		return make_unique<RedirHandler>(stream, cat);
	}

private:
	vector<Category> categories;
	MsgCatID nextId = 23; // it could be 0... doesn't matter why it's 23
	IOutputWindow *outputWindow = nullptr;
	mutex m;
	MessagePrinterSettings settings;
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
