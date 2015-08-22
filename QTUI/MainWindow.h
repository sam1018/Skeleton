#pragma once

#include "../SkeletonInterface/IMainWindow.h"
#include <memory>

class MainWindowImpl;
class OpenGLWindow;
class OutputWindow;

class MainWindow : public GUI::IMainWindow
{
public:
	MainWindow();
	~MainWindow();

	void Show();

private:
	// Implementation class for MainWindow
	std::unique_ptr <MainWindowImpl> mainWindowImpl;

	///////////////////////////////////////////////////////////////////////////
	// Start window declaration
	///////////////////////////////////////////////////////////////////////////
	// All other windows that main window requires
	// Window here don't mean, their implementation needs to be QWindow
	// Their implementation can widget, window or anything else
	// as long as they are usable by mainWindowImpl
	///////////////////////////////////////////////////////////////////////////

	std::unique_ptr<OpenGLWindow> openGLWindow;
	std::unique_ptr<OutputWindow> outputWindow;

	///////////////////////////////////////////////////////////////////////////
	// End window declaration
	///////////////////////////////////////////////////////////////////////////

};
