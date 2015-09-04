#pragma once

#include "UI/IMainWindow.h"
#include <memory>

class MainWindowImpl;
class OpenGLWindow;
class OutputWindow;
class PluginExplorer;
class CommonControls;

class MainWindow : public MW::IMainWindow
{
public:
	MainWindow();
	~MainWindow();

	void* GetImpl();

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
	std::unique_ptr<PluginExplorer> pluginExplorer;
	std::unique_ptr<CommonControls> commonControls;

	///////////////////////////////////////////////////////////////////////////
	// End window declaration
	///////////////////////////////////////////////////////////////////////////

};
