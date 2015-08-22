#include "MainWindow.h"
#include "OpenGLWindow.h"
#include "MainWindowImpl.h"


///////////////////////////////////////////////////////////////////////////////
/////////////          MainWindow Definition                       ////////////
///////////////////////////////////////////////////////////////////////////////


MainWindow::MainWindow() :
	mainWindowImpl{ std::make_unique <MainWindowImpl>() },
	openGLWindow{ std::make_unique<OpenGLWindow>() }
{
	mainWindowImpl->setCentralWidget(QWidget::createWindowContainer(openGLWindow->GetOpenGLWindowImpl()));
}


MainWindow::~MainWindow()
{
}

void MainWindow::Show()
{
	mainWindowImpl->Show();
}
