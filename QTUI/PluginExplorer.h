#pragma once

#include "../SkeletonInterface/IPluginExplorer.h"
#include <memory>

class QDockWidget;
class PluginExplorerImpl;

class PluginExplorer : public PE::IPluginExplorer
{
public:
	PluginExplorer();
	~PluginExplorer();

	void* GetImpl();

	void AddPluginDataToTree(const std::string &pluginName, const std::vector<std::string> &functions);

	QDockWidget* GetDockWidget();

private:
	std::unique_ptr<PluginExplorerImpl> pluginExplorerImpl;
};
