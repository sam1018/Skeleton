#pragma once

#include "UI/IOutputWindow.h"

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
	virtual void SetComboCategoryChangedCallback_(std::function<void(const std::string&)> callback);


private:
	// MainWindow will delete it's child controls
	OutputWindowImpl *outputWindowImpl;
};
