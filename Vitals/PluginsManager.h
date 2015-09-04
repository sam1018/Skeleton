#pragma once

#include <memory>
#include <string>
#include "Vitals\IPluginsManager.h"

class Plugin;


class PluginsManager : public VT::IPluginsManager
{
public:
	PluginsManager();
	~PluginsManager();

private:
	void ExecuteFunctionDynamic_(std::string pluginName, std::string functionName);

	// Returns the asked plugin
	// Loads the plugin if not already loaded
	// Returns nullptr if the plugin cannot be loaded
	Plugin* GetDynamicPlugin(std::string pluginName);

private:
	struct PluginsManagerImpl;
	// We can safely ignore C4251 in this case
#pragma warning( push )
#pragma warning( disable : 4251 )
	std::unique_ptr <PluginsManagerImpl> pluginsManagerImpl;
#pragma warning( pop )
};
