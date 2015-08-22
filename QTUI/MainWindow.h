#pragma once

#include "../SkeletonInterface/IMainWindow.h"
#include <memory>

class MainWindowImpl;
class OpenGLWindow;

class MainWindow : public GUI::IMainWindow
{
public:
	MainWindow();
	~MainWindow();

	void Show();

private:
	// Implementation class for MainWindow
	std::unique_ptr <MainWindowImpl> mainWindowImpl;

	// Other windows that main windows needs
	std::unique_ptr <OpenGLWindow> openGLWindow;
};
