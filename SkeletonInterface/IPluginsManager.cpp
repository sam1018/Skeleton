#include "Vitals\IPluginsManager.h"

using namespace VT;
using namespace std;

void IPluginsManager::ExecuteFunction(const string &pluginName, const string &functionName)
{
	ExecuteFunction_(pluginName, functionName);
}

bool IPluginsManager::IsPluginLoaded(const std::string & pluginName)
{
	return IsPluginLoaded_(pluginName);
}

IPlugin* IPluginsManager::LoadPlugin(const string &pluginName)
{
	return LoadPlugin_(pluginName);
}
