#pragma once

#include "../SkeletonInterface/IMainWindow.h"
#include <memory>

class MainWindowImpl;
class OpenGLWindow;

class MainWindow : public GUI::IMainWindow
{
public:
	MainWindow(OpenGLWindow *pOpenGLWindow);
	~MainWindow();

	void Show();

private:
	std::unique_ptr <MainWindowImpl> mainWindowImpl;
};
