#pragma once

#include "UI/IOutputWindow.h"
#include <memory>

class OutputWindowImpl;
class QDockWidget;

class OutputWindow : public OutWnd::IOutputWindow
{
public:
	OutputWindow();
	~OutputWindow();

	void* GetImpl();

	void AddCategory(const std::string &categoryName);
	void Refresh(const std::string &categoryName, const std::string &text);

	QDockWidget* GetDockWidget();

private:
	std::unique_ptr<OutputWindowImpl> outputWindowImpl;
};
