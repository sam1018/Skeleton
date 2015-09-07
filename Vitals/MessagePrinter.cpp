#include "MessagePrinter.h"
#include "UI\IOutputWindow.h"
#include <vector>
#include <algorithm>
#include <mutex>
#include <iostream>


using namespace UI;
using namespace VT;
using namespace std;


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

public:
	void SetOutputWindow(IOutputWindow *param)
	{
		outputWindow = param;

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

	void OutputWindowSetText(MsgCatID id, const string &text, bool append, bool makeCurrrentCategory)
	{
		lock_guard<mutex> lock(m);

		auto iter = GetCategoryByID(id);

		ThrowIfItemNotFound(iter, to_string(id));

		if (append)
			iter->text += text;
		else
			iter->text = text;

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
				cout << text << "\n";
			}
		}
	}

private:
	vector<Category> categories;
	MsgCatID nextId = 23; // it could be 0... doesn't matter why it's 23
	IOutputWindow *outputWindow = nullptr;
	mutex m;
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

void MessagePrinter::PrintMessage_(MsgCatID id,
	const string &text, bool append, bool makeCurrrentCategory)
{
	messagePrinterImpl->OutputWindowSetText(id, text, append, makeCurrrentCategory);
}

void MessagePrinter::SetOutputWindow_(IOutputWindow * wnd)
{
	messagePrinterImpl->SetOutputWindow(wnd);
}
