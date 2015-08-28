#include "MainWindow.h"
#include "OpenGLWindow.h"
#include "OutputWindow.h"
#include "PluginExplorer.h"
#include "MainWindowImpl.h"
#include "CommonControls.h"


///////////////////////////////////////////////////////////////////////////////
/////////////          MainWindow Definition                       ////////////
///////////////////////////////////////////////////////////////////////////////


MainWindow::MainWindow() :
	mainWindowImpl{ std::make_unique <MainWindowImpl>() },
	openGLWindow{ std::make_unique<OpenGLWindow>() },
	outputWindow{ std::make_unique<OutputWindow>() },
	pluginExplorer{ std::make_unique<PluginExplorer>() },
	commonControls{ std::make_unique<CommonControls>() }
{
	mainWindowImpl->setCentralWidget(QWidget::createWindowContainer(openGLWindow->GetOpenGLWindowImpl()));
	mainWindowImpl->addDockWidget(Qt::DockWidgetArea::BottomDockWidgetArea, outputWindow->GetDockWidget());
	mainWindowImpl->addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, pluginExplorer->GetDockWidget());
}


MainWindow::~MainWindow()
{
}

void* MainWindow::GetImpl()
{
	return mainWindowImpl.get();
}

void MainWindow::Show()
{
	mainWindowImpl->Show();
}
