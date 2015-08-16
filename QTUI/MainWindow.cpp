#include "MainWindow.h"
#include "MainWindowImpl.h"

MainWindow::MainWindow(OpenGLWindow *pOpenGLWindow) :
	m_pMainWindowImpl{ std::make_unique <MainWindowImpl> (pOpenGLWindow) }
{
}


MainWindow::~MainWindow()
{
}

void MainWindow::Show()
{
	m_pMainWindowImpl->Show();
}
