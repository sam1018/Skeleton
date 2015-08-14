#pragma once

#include "../SkeletonInterface/IMainWindow.h"
#include <memory>

class MainWindowImpl;

class MainWindow : public IMainWindow
{
public:
	MainWindow();
	~MainWindow();

	void Show();

private:
	std::unique_ptr <MainWindowImpl> m_pMainWindowImpl;
};
