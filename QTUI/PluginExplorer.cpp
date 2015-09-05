#include "PluginExplorer.h"
#include "PluginExplorerImpl.h"


PluginExplorer::PluginExplorer() :
	pluginExplorerImpl{ std::make_unique<PluginExplorerImpl>(this) }
{
}


PluginExplorer::~PluginExplorer()
{
}

void* PluginExplorer::GetControlImplementationSpecific_()
{
	return pluginExplorerImpl.get();
}

void PluginExplorer::AddPluginDataToTree_(const std::string &pluginName, 
	const std::vector<std::string> &functions)
{
	pluginExplorerImpl->AddPluginDataToTree(pluginName, functions);
}

QDockWidget* PluginExplorer::GetDockWidget()
{
	return pluginExplorerImpl.get();
}
