#include "UI\IOutputWindow.h"
#include <vector>
#include <algorithm>

using namespace UI;
using namespace std;


IOutputWindow::IOutputWindow()
{
}


IOutputWindow::~IOutputWindow()
{
}

void IOutputWindow::AddCategory(const string &categoryName)
{
	AddCategory_(categoryName);
}

void IOutputWindow::Refresh(const string &categoryName, const string &text)
{
	Refresh_(categoryName, text);
}

void UI::IOutputWindow::SetComboCategoryChangedCallback(std::function<void(const std::string&)> callback)
{
	SetComboCategoryChangedCallback_(callback);
}
