#include "OutputWindow.h"
#include <QtWidgets\QDockWidget>


OutputWindow::OutputWindow() :
	outputWindow{ std::make_unique<QDockWidget>() }
{
	outputWindow->setObjectName("Output Window");
}


OutputWindow::~OutputWindow()
{
}

QDockWidget* OutputWindow::GetDockWidget()
{
	return outputWindow.get();
}
