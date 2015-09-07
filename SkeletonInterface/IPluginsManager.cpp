#include "Vitals\IPluginsManager.h"

using namespace VT;
using namespace std;

void IPluginsManager::ExecuteFunction(const string &pluginName, const string &functionName)
{
	ExecuteFunction_(pluginName, functionName);
}
