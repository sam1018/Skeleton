#include "IMainWindow.h"

using namespace GUI;

IMainWindow *mainWindow;

void GUI::Show()
{
	if (!mainWindow)
		ThrowUninitializedClass("IMainWindow");
	mainWindow->Show();
}


///////////////////////////////////////////////////////////////////////////////
/////////////          IMainWindow Definition                      ////////////
///////////////////////////////////////////////////////////////////////////////


IMainWindow::IMainWindow()
{
	mainWindow = this;
}

IMainWindow::~IMainWindow()
{
	mainWindow = nullptr;
}

