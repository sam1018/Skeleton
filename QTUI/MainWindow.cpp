#include "MainWindow.h"
#include "OpenGLWindow.h"
#include "PluginExplorer.h"
#include "MainWindowImpl.h"
#include "OutputWindow.h"

using namespace std;


///////////////////////////////////////////////////////////////////////////////
/////////////          MainWindow Definition                       ////////////
///////////////////////////////////////////////////////////////////////////////


MainWindow::MainWindow(OpenGLWindow *oglWnd, OutputWindow *outWnd) :
	mainWindowImpl{ make_unique <MainWindowImpl>() },
	pluginExplorer{ make_unique<PluginExplorer>() }
{
	mainWindowImpl->setCentralWidget(QWidget::createWindowContainer(oglWnd->GetOpenGLWindowImpl()));
	mainWindowImpl->addDockWidget(Qt::DockWidgetArea::BottomDockWidgetArea, outWnd->GetDockWidget());
	mainWindowImpl->addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, pluginExplorer->GetDockWidget());
}


MainWindow::~MainWindow()
{
}

void MainWindow::Show_()
{
	mainWindowImpl->Show();
}
