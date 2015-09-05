#pragma once

#include "UI/IOutputWindow.h"
#include <memory>

class OutputWindowImpl;
class QDockWidget;

class OutputWindow : public UI::IOutputWindow
{
public:
	OutputWindow();
	~OutputWindow();

	QDockWidget* GetDockWidget();

private:
	virtual void AddCategory_(const std::string &categoryName);
	virtual void Refresh_(const std::string &categoryName, const std::string &text);


private:
	std::unique_ptr<OutputWindowImpl> outputWindowImpl;
};
