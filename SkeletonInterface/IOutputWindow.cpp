#include "UI\IOutputWindow.h"
#include <vector>
#include <algorithm>

using namespace UI;


IOutputWindow::IOutputWindow()
{
}


IOutputWindow::~IOutputWindow()
{
}

void IOutputWindow::AddCategory(const std::string &categoryName)
{
	AddCategory_(categoryName);
}

void IOutputWindow::Refresh(const std::string &categoryName, const std::string &text)
{
	Refresh_(categoryName, text);
}
