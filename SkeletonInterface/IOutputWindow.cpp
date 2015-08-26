#include "IOutputWindow.h"
#include <mutex>
#include <vector>
#include <algorithm>

using namespace OutWnd;

const std::string OutWnd::OutWndPluginExplorerCategory{ "Plugin Explorer" };

class OutWndImpl
{
	struct Category
	{
		OutWndCatID id;
		std::string categoryName;
		std::string text;
	};

	using Categories = std::vector<Category>;
	using CategoryIter = std::vector<Category>::iterator;

	CategoryIter GetCategoryByName(std::string categoryName)
	{
		return std::find_if(categories.begin(), categories.end(),
			[categoryName](auto &item) { return item.categoryName == categoryName; });
	}

	CategoryIter GetCategoryByID(OutWndCatID id)
	{
		return std::find_if(categories.begin(), categories.end(),
			[id](auto &item) { return item.id == id; });
	}

	void ThrowIfItemNotFound(CategoryIter iter, std::string item)
	{
		if (iter == categories.end())
			throw std::runtime_error((item + ": No such output window category.").c_str());
	}

	OutWndImpl() {}
	~OutWndImpl() {}

public:
	static OutWndImpl& GetInstance()
	{
		static OutWndImpl theOutWndImpl;
		return theOutWndImpl;
	}

	void SetOutputWindow(IOutputWindow *param)
	{
		outputWindow = param;

		if (outputWindow)
		{
			for (auto &item : categories)
				outputWindow->AddCategory(item.categoryName);
		}
	}

	OutWndCatID RegisterOutputWindowCategory(std::string categoryName)
	{
		std::lock_guard<std::mutex> lock(m);

		auto iter = GetCategoryByName(categoryName);

		OutWndCatID ret = nextId;
		if (iter == categories.end())
		{
			categories.push_back(Category{ nextId++, categoryName, "" });

			if (outputWindow)
				outputWindow->AddCategory(categoryName);
		}
		else
			ret = iter->id;

		return ret;
	}

	void OutputWindowSetText(OutWndCatID id, std::string text, bool append, bool makeCurrrentCategory)
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
				outputWindow->SetCategory(iter->categoryName);

			outputWindow->UpdateText(iter->categoryName.c_str());
		}
	}

	// Throws if categoryName is not a valid category
	std::string GetTextForCategory(std::string categoryName)
	{
		auto iter = GetCategoryByName(categoryName);

		ThrowIfItemNotFound(iter, categoryName);

		return iter->text;
	}

private:
	std::vector<Category> categories;
	OutWndCatID nextId = 23; // it could be 0... doesn't matter why it's 23
	IOutputWindow *outputWindow = nullptr;
	std::mutex m;
};

IOutputWindow::IOutputWindow()
{
}


IOutputWindow::~IOutputWindow()
{
}


void IOutputWindow::InitializeItem()
{
	OutWndImpl::GetInstance().SetOutputWindow(this);
}

void IOutputWindow::Cleanup()
{
	OutWndImpl::GetInstance().SetOutputWindow(nullptr);
}

std::string IOutputWindow::GetTextForCategory(std::string categoryName)
{
	return OutWndImpl::GetInstance().GetTextForCategory(categoryName);
}

OutWnd::OutWndCatID OutWnd::RegisterOutputWindowCategory(std::string categoryName)
{
	return OutWndImpl::GetInstance().RegisterOutputWindowCategory(categoryName);
}

void OutWnd::OutputWindowSetText(OutWndCatID id, std::string text, bool append, bool makeCurrrentCategory)
{
	OutWndImpl::GetInstance().OutputWindowSetText(id, text, append, makeCurrrentCategory);
}
