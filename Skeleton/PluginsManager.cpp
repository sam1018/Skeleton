#include "PluginsManager.h"
#include "Plugin.h"
#include "SkeletonSettings.h"
#include <array>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>


using PluginsArray = std::array <std::unique_ptr<Plugin>, PluginTypeCount()>;


struct PluginsManager::PluginsManagerImpl
{
	PluginsArray pluginsArray;
};


///////////////////////////////////////////////////////////////////////////////
/////////////          PluginsManager Definition                   ////////////
///////////////////////////////////////////////////////////////////////////////


PluginsManager::PluginsManager() :
	pluginsManagerImpl{ std::make_unique<PluginsManager::PluginsManagerImpl>() }
{
	LoadPlugins();
}

PluginsManager::~PluginsManager()
{
}

void PluginsManager::LoadPlugins()
{
	pluginsManagerImpl->pluginsArray[PluginIndex(PluginType::QTUI)] =
		std::make_unique<Plugin>(SkeletonSettings::GetInstance().uiPluginName);
}

void PluginsManager::Initialize(int argc, char **argv)
{
	for (auto &p : pluginsManagerImpl->pluginsArray)
		p->PluginInitialize(argc, argv);
}
