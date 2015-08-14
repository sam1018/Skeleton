#include "MainWindow.h"
#include "MainWindowImpl.h"

MainWindow::MainWindow() : 
	m_pMainWindowImpl{ std::make_unique <MainWindowImpl> () }
{
}


MainWindow::~MainWindow()
{
}

void MainWindow::Show()
{
	m_pMainWindowImpl->Show();
}
