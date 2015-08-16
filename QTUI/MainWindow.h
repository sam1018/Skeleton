#pragma once

#include "../SkeletonInterface/IMainWindow.h"
#include <memory>

class MainWindowImpl;
class OpenGLWindow;

class MainWindow : public IMainWindow
{
public:
	MainWindow(OpenGLWindow *pOpenGLWindow);
	~MainWindow();

	void Show();

private:
	std::unique_ptr <MainWindowImpl> m_pMainWindowImpl;
};
