#include "Plugin.h"
#include "Routines.h"
#include "PluginsManager.h"
#include "CallerManager.h"
#include "UI/IOutputWindow.h"
#include "UI/IPluginExplorer.h"
#include "Vitals\IVitalsInterfaceManager.h"
#include <array>
#include <functional>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

using namespace VT;

using PluginsArrayDynamic = std::vector<std::unique_ptr<Plugin>>;


struct PluginsManager::PluginsManagerImpl
{
	PluginsArrayDynamic pluginsArrayDynamic;
};


///////////////////////////////////////////////////////////////////////////////
/////////////          PluginsManager Definition                   ////////////
///////////////////////////////////////////////////////////////////////////////


PluginsManager::PluginsManager() :
	pluginsManagerImpl{ std::make_unique<PluginsManager::PluginsManagerImpl>() }
{
}

PluginsManager::~PluginsManager()
{
}

void PluginsManager::ExecuteFunction_(const std::string &pluginName, const std::string &functionName)
{
	Plugin *plugin = GetDynamicPlugin(pluginName);

	if (plugin == nullptr)
		ThrowPluginLoadFailure(pluginName);

	std::function<void(void)> f = (void(*)(void))plugin->GetFunctionAddress(functionName);
	GetCallerManager()->RegisterCaller(CreateCaller(f, plugin), CallType::OneTime);
}

Plugin* PluginsManager::GetDynamicPlugin(const std::string &pluginName)
{
	for (auto &plugin : pluginsManagerImpl->pluginsArrayDynamic)
	{
		if (Routines::IsSamePath(plugin->GetPluginName(), pluginName))
			return plugin.get();
	}

	std::unique_ptr<Plugin> plugin{ std::make_unique<Plugin>(pluginName) };

	Plugin *ret = plugin.get(); // store return result before moving
	pluginsManagerImpl->pluginsArrayDynamic.push_back(std::move(plugin));

	return ret;
}
