#include "PluginExplorer.h"
#include "PluginExplorerImpl.h"


PluginExplorer::PluginExplorer() :
	pluginExplorerImpl{ std::make_unique<PluginExplorerImpl>(this) }
{
}


PluginExplorer::~PluginExplorer()
{
}

QDockWidget* PluginExplorer::GetDockWidget()
{
	return pluginExplorerImpl.get();
}
