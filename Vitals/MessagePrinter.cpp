#include "MessagePrinter.h"
#include "UI\IOutputWindow.h"
#include <vector>
#include <algorithm>
#include <mutex>


class MessagePrinter::MessagePrinterImpl
{
	struct Category
	{
		VT::MsgCatID id;
		std::string categoryName;
		std::string text;
	};

	using Categories = std::vector<Category>;
	using CategoryIter = std::vector<Category>::iterator;

	CategoryIter GetCategoryByName(const std::string &categoryName)
	{
		return std::find_if(categories.begin(), categories.end(),
			[categoryName](auto &item) { return item.categoryName == categoryName; });
	}

	CategoryIter GetCategoryByID(VT::MsgCatID id)
	{
		return std::find_if(categories.begin(), categories.end(),
			[id](auto &item) { return item.id == id; });
	}

	void ThrowIfItemNotFound(CategoryIter iter, const std::string &item)
	{
		if (iter == categories.end())
			throw std::runtime_error((item + ": No such output window category.").c_str());
	}

public:
	//void SetOutputWindow(UI::IOutputWindow *param)
	//{
	//	outputWindow = param;

	//	if (outputWindow)
	//	{
	//		for (auto &item : categories)
	//			outputWindow->AddCategory(item.categoryName);
	//	}
	//}

	VT::MsgCatID RegisterOutputWindowCategory(const std::string &categoryName)
	{
		std::lock_guard<std::mutex> lock(m);

		auto iter = GetCategoryByName(categoryName);

		VT::MsgCatID ret = nextId;
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

	void OutputWindowSetText(VT::MsgCatID id, const std::string &text, bool append, bool makeCurrrentCategory)
	{
		std::lock_guard<std::mutex> lock(m);

		auto iter = GetCategoryByID(id);

		ThrowIfItemNotFound(iter, std::to_string(id));

		if (append)
			iter->text += text;
		else
			iter->text = text;

		if (outputWindow)
		{
			if (makeCurrrentCategory)
			{
				// This function may get called outside of main thread
				// QT Plugin needs to make sure this situation is properly handled
				// Because, in QT this is not acceptable to send event to an object outside of GUI thread
				outputWindow->Refresh(iter->categoryName, iter->text);
			}
		}
	}

private:
	std::vector<Category> categories;
	VT::MsgCatID nextId = 23; // it could be 0... doesn't matter why it's 23
	UI::IOutputWindow *outputWindow = nullptr;
	std::mutex m;
};



MessagePrinter::MessagePrinter() :
	messagePrinterImpl{ std::make_unique<MessagePrinterImpl>() }
{
	VT::MsgCat_PluginExplorer = RegisterMessageCategory("Plugin Explorer");
	VT::MsgCat_ErrorMsg = RegisterMessageCategory("Error Message");
}

MessagePrinter::~MessagePrinter()
{
}

VT::MsgCatID MessagePrinter::RegisterMessageCategory_(const std::string &categoryName)
{
	return messagePrinterImpl->RegisterOutputWindowCategory(categoryName);
}

void MessagePrinter::PrintMessage_(VT::MsgCatID id,
	const std::string &text, bool append, bool makeCurrrentCategory)
{
	messagePrinterImpl->OutputWindowSetText(id, text, append, makeCurrrentCategory);
}
