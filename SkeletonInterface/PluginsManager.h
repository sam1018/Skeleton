#pragma once

#include "SkeletonInterface.h"
#include <memory>
#include <string>

enum class PluginType
{
	QTUI,
	TOTAL
};

constexpr int PluginTypeCount()
{
	return static_cast<int>(PluginType::TOTAL);
}

constexpr int PluginIndex(PluginType pluginType)
{
	return static_cast<int>(pluginType);
}

class Plugin;

class SKELETONINTERFACE_DECLSPEC PluginsManager
{
private:
	PluginsManager();
	~PluginsManager();

public:
	static PluginsManager& GetInstance();

	void LoadPluginsStatic();

	void Initialize(int argc, char **argv);
	void Destroy();

	void ExecuteFunctionDynamic(std::string pluginName, std::string functionName);

private:
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