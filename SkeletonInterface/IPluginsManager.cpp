#include "Vitals\IPluginsManager.h"

using namespace VT;

void IPluginsManager::ExecuteFunctionDynamic(std::string pluginName, std::string functionName)
{
	ExecuteFunctionDynamic_(pluginName, functionName);
}
