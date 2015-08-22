#pragma once

#include "../SkeletonInterface/IOutputWindow.h"
#include <memory>

class QDockWidget;

class OutputWindow : public GUI::IOutputWindow
{
public:
	OutputWindow();
	~OutputWindow();

	QDockWidget* GetDockWidget();

private:
	std::unique_ptr<QDockWidget> outputWindow;
};
