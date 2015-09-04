#include "UI\IMainWindow.h"

using namespace MW;

IMainWindow *mainWindow;

void MW::Show()
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
}

IMainWindow::~IMainWindow()
{
}

void IMainWindow::InitializeItem()
{
	mainWindow = this;
}

void IMainWindow::Cleanup()
{
	mainWindow = nullptr;
}
