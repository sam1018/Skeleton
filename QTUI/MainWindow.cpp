#include "MainWindow.h"
#include "OpenGLWindow.h"
#include "OutputWindow.h"
#include "PluginExplorer.h"
#include "MainWindowImpl.h"


///////////////////////////////////////////////////////////////////////////////
/////////////          MainWindow Definition                       ////////////
///////////////////////////////////////////////////////////////////////////////


MainWindow::MainWindow(OpenGLWindow *oglWnd) :
	mainWindowImpl{ std::make_unique <MainWindowImpl>() },
	outputWindow{ std::make_unique<OutputWindow>() },
	pluginExplorer{ std::make_unique<PluginExplorer>() }
{
	mainWindowImpl->setCentralWidget(QWidget::createWindowContainer(oglWnd->GetOpenGLWindowImpl()));
	mainWindowImpl->addDockWidget(Qt::DockWidgetArea::BottomDockWidgetArea, outputWindow->GetDockWidget());
	mainWindowImpl->addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, pluginExplorer->GetDockWidget());
}


MainWindow::~MainWindow()
{
}

void MainWindow::Show_()
{
	mainWindowImpl->Show();
}
