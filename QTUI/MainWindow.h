#pragma once

#include "../SkeletonInterface/IMainWindow.h"
#include <memory>

class MainWindow : public IMainWindow
{
public:
	MainWindow();
	~MainWindow();

	void Show();

private:
	void CreateToolbars();

private:
	struct ImplData;
	std::unique_ptr <ImplData> m_pImplData;
};
