#include "Vitals\IPluginsManager.h"

using namespace VT;

void IPluginsManager::ExecuteFunction(const std::string &pluginName, const std::string &functionName)
{
	ExecuteFunction_(pluginName, functionName);
}
