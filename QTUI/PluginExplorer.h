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

	QDockWidget* GetDockWidget();

private:
	std::unique_ptr<PluginExplorerImpl> pluginExplorerImpl;
};
