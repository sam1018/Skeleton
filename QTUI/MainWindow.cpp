#include "MainWindow.h"
#include "OpenGLWindow.h"
#include "OutputWindow.h"
#include "TBCallControl.h"
#include "PluginExplorer.h"
#include "MainWindowImpl.h"

using namespace std;


///////////////////////////////////////////////////////////////////////////////
/////////////          MainWindow Definition                       ////////////
///////////////////////////////////////////////////////////////////////////////


MainWindow::MainWindow(OpenGLWindow *oglWnd, OutputWindow *outWnd, TBCallControl *tbCallControl) :
	mainWindowImpl{ make_unique <MainWindowImpl>() },
	pluginExplorer{ make_unique<PluginExplorer>() }
{
	mainWindowImpl->setCentralWidget(QWidget::createWindowContainer(oglWnd->GetOpenGLWindowImpl()));
	mainWindowImpl->addDockWidget(Qt::DockWidgetArea::BottomDockWidgetArea, outWnd->GetDockWidget());
	mainWindowImpl->addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, pluginExplorer->GetDockWidget());
	tbCallControl->SetToolbar(mainWindowImpl->addToolBar("Call Control"));
}


MainWindow::~MainWindow()
{
}

void MainWindow::Show_()
{
	mainWindowImpl->Show();
}
