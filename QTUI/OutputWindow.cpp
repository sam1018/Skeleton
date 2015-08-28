#include "OutputWindow.h"
#include "OutputWindowImpl.h"


OutputWindow::OutputWindow() :
	outputWindowImpl{ std::make_unique<OutputWindowImpl>(this) }
{
}


OutputWindow::~OutputWindow()
{
}

void* OutputWindow::GetImpl()
{
	return outputWindowImpl.get();
}

void OutputWindow::AddCategory(const std::string &categoryName)
{
	outputWindowImpl->AddCategory(categoryName);
}

void OutputWindow::Refresh(const std::string &categoryName, const std::string &text)
{
	outputWindowImpl->Refresh(categoryName, text);
}

QDockWidget* OutputWindow::GetDockWidget()
{
	return outputWindowImpl.get();
}
