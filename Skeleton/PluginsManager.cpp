#include "PluginsManager.h"
#include "Plugin.h"
#include "SkeletonSettings.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <array>

using PluginsArray = std::array <std::unique_ptr<Plugin>, PluginTypeCount()>;

struct PluginsManager::PluginsManagerImpl
{
	PluginsArray m_PluginsArray;
};

PluginsManager::PluginsManager() :
	m_pImpl {std::make_unique<PluginsManager::PluginsManagerImpl>()}
{
	LoadPlugins();
}

PluginsManager::~PluginsManager()
{
}

void PluginsManager::LoadPlugins()
{
	m_pImpl->m_PluginsArray[PluginIndex(PluginType::QTUI)] = 
		std::make_unique<Plugin>(SkeletonSettings::GetInstance().UIPluginName());
}

void PluginsManager::Initialize(int argc, char **argv)
{
	for (auto &p : m_pImpl->m_PluginsArray)
		p->PluginInitialize(argc, argv);
}
