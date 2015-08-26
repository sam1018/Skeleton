#include "PluginsManager.h"
#include "Plugin.h"
#include "Routines.h"
#include "StaticPlugins.h"
#include "IOutputWindow.h"
#include "IPluginExplorer.h"
#include <array>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>


using PluginsArrayStatic = std::array<std::unique_ptr<Plugin>, PluginTypeCount()>;
using PluginsArrayDynamic = std::vector<std::unique_ptr<Plugin>>;


struct PluginsManager::PluginsManagerImpl
{
	PluginsArrayStatic pluginsArrayStatic;
	PluginsArrayDynamic pluginsArrayDynamic;
};


constexpr auto settingsFile{ "StaticPlugins.xml" };


///////////////////////////////////////////////////////////////////////////////
/////////////          PluginsManager Definition                   ////////////
///////////////////////////////////////////////////////////////////////////////


PluginsManager::PluginsManager() :
	pluginsManagerImpl{ std::make_unique<PluginsManager::PluginsManagerImpl>() }
{
	StaticPlugins::GetInstance().Load(Routines::GetSettingsFileFullPath_Load(settingsFile));
	LoadPluginsStatic();
}

PluginsManager::~PluginsManager()
{
}

PluginsManager& PluginsManager::GetInstance()
{
	static PluginsManager thePluginsManager;
	return thePluginsManager;
}

void PluginsManager::LoadPluginsStatic()
{
	pluginsManagerImpl->pluginsArrayStatic[PluginIndex(PluginType::QTUI)] =
		std::make_unique<Plugin>(StaticPlugins::GetInstance().uiPluginName);
}

void PluginsManager::Initialize(int argc, char **argv)
{
	for (auto &p : pluginsManagerImpl->pluginsArrayStatic)
		p->PluginInitialize(argc, argv);
}

void PluginsManager::Destroy()
{
	for (auto &p : pluginsManagerImpl->pluginsArrayStatic)
		p->PluginDestroy();
}

void PluginsManager::ExecuteFunctionDynamic(std::string pluginName, std::string functionName)
{
	Plugin *plugin = GetDynamicPlugin(pluginName);

	if (plugin == nullptr)
		ThrowPluginLoadFailure(pluginName);

	plugin->PluginCallerBody<void>(functionName);
}

Plugin* PluginsManager::GetDynamicPlugin(std::string pluginName)
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
