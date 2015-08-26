#pragma once

#include "../SkeletonInterface/IOutputWindow.h"
#include <memory>

class OutputWindowImpl;
class QDockWidget;

class OutputWindow : public OutWnd::IOutputWindow
{
public:
	OutputWindow();
	~OutputWindow();

	void AddCategory(std::string categoryName);
	void SetCategory(std::string categoryName);
	void UpdateText(std::string categoryName);

	QDockWidget* GetDockWidget();

private:
	std::unique_ptr<OutputWindowImpl> outputWindowImpl;
};
