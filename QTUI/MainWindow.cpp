#include "MainWindow.h"
#include "OpenGLWindow.h"
#include "OutputWindow.h"
#include "MainWindowImpl.h"


///////////////////////////////////////////////////////////////////////////////
/////////////          MainWindow Definition                       ////////////
///////////////////////////////////////////////////////////////////////////////


MainWindow::MainWindow() :
	mainWindowImpl{ std::make_unique <MainWindowImpl>() },
	openGLWindow{ std::make_unique<OpenGLWindow>() },
	outputWindow{ std::make_unique<OutputWindow>() }
{
	mainWindowImpl->setCentralWidget(QWidget::createWindowContainer(openGLWindow->GetOpenGLWindowImpl()));
	mainWindowImpl->addDockWidget(Qt::DockWidgetArea::BottomDockWidgetArea, outputWindow->GetDockWidget());
}


MainWindow::~MainWindow()
{
}

void MainWindow::Show()
{
	mainWindowImpl->Show();
}
