#include "OutputWindow.h"
#include "OutputWindowImpl.h"


OutputWindow::OutputWindow() :
	outputWindowImpl{ std::make_unique<OutputWindowImpl>(this) }
{
}


OutputWindow::~OutputWindow()
{
}

void OutputWindow::AddCategory(std::string categoryName)
{
	outputWindowImpl->AddCategory(categoryName);
}

void OutputWindow::SetCategory(std::string categoryName)
{
	outputWindowImpl->SetCategory(categoryName);
}

void OutputWindow::UpdateText(std::string categoryName)
{
	outputWindowImpl->UpdateText(categoryName.c_str());
}

QDockWidget* OutputWindow::GetDockWidget()
{
	return outputWindowImpl.get();
}
