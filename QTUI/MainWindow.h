#pragma once

#include "UI/IMainWindow.h"
#include <memory>

class MainWindowImpl;
class OpenGLWindow;
class OutputWindow;
class PluginExplorer;
class CommonControls;

class MainWindow : public UI::IMainWindow
{
public:
	MainWindow(OpenGLWindow *oglWnd);
	~MainWindow();

private:
	void Show_();

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

	std::unique_ptr<OutputWindow> outputWindow;
	std::unique_ptr<PluginExplorer> pluginExplorer;

	///////////////////////////////////////////////////////////////////////////
	// End window declaration
	///////////////////////////////////////////////////////////////////////////

};
