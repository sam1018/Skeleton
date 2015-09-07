#include "PluginExplorer.h"
#include "PluginExplorerImpl.h"

using namespace std;


PluginExplorer::PluginExplorer() :
	pluginExplorerImpl{ make_unique<PluginExplorerImpl>(this) }
{
}


PluginExplorer::~PluginExplorer()
{
}

void* PluginExplorer::GetControlImplementationSpecific_()
{
	return pluginExplorerImpl.get();
}

void PluginExplorer::AddPluginDataToTree_(const string &pluginName, 
	const vector<string> &functions)
{
	pluginExplorerImpl->AddPluginDataToTree(pluginName, functions);
}

QDockWidget* PluginExplorer::GetDockWidget()
{
	return pluginExplorerImpl.get();
}
