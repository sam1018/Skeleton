#include "OutputWindow.h"
#include "OutputWindowImpl.h"

using namespace std;


OutputWindow::OutputWindow()
{
	outputWindowImpl = new OutputWindowImpl(this);
}


OutputWindow::~OutputWindow()
{
}

void OutputWindow::AddCategory_(const string &categoryName)
{
	outputWindowImpl->AddCategory(categoryName);
}

void OutputWindow::Refresh_(const string &categoryName, const string &text)
{
	outputWindowImpl->Refresh(categoryName, text);
}

QDockWidget* OutputWindow::GetDockWidget()
{
	return outputWindowImpl;
}
