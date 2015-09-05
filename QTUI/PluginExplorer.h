#pragma once

#include "UI/IPluginExplorer.h"
#include <memory>

class QDockWidget;
class PluginExplorerImpl;

class PluginExplorer : public UI::IPluginExplorer
{
public:
	PluginExplorer();
	~PluginExplorer();

	QDockWidget* GetDockWidget();

private:
	virtual void AddPluginDataToTree_(const std::string &pluginName, 
		const std::vector<std::string> &functions);
	virtual void* GetControlImplementationSpecific_();

private:
	std::unique_ptr<PluginExplorerImpl> pluginExplorerImpl;
};
