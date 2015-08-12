#include "MainWindow.h"
#include <QtWidgets\qmainwindow.h>

struct MainWindow::ImplData
{
	QMainWindow mainWnd;
};

MainWindow::MainWindow() : m_pImplData{ std::make_unique <ImplData> () }
{
}


MainWindow::~MainWindow()
{
}

void MainWindow::Show()
{
	m_pImplData->mainWnd.show();
}
