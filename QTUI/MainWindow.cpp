#include "MainWindow.h"
#include "MainWindowImpl.h"


///////////////////////////////////////////////////////////////////////////////
/////////////          MainWindow Definition                       ////////////
///////////////////////////////////////////////////////////////////////////////


MainWindow::MainWindow(OpenGLWindow *openGLWindow) :
	mainWindowImpl{ std::make_unique <MainWindowImpl>(openGLWindow) }
{
}


MainWindow::~MainWindow()
{
}

void MainWindow::Show()
{
	mainWindowImpl->Show();
}
