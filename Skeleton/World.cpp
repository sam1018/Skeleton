#include "World.h"
#include "PluginUI.h"
#include "../SkeletonInterface/IMainWindow.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

namespace pt = boost::property_tree;

struct World::ImplData
{
	IMainWindow* m_pMainWindow;
	PluginUI pluginUI;
};

World::World() : m_pImplData {std::make_unique<World::ImplData>()}
{
}

World::~World()
{
}

World& World::GetInstance()
{
	static World theWorld;
	return theWorld;
}

void World::LoadPlugins(std::string fileName)
{
	pt::ptree tree;
	pt::read_xml(fileName, tree);

	m_pImplData->pluginUI.LoadModule(tree.get("PluginsList.UIPlugin", "QTUI"));
	m_pImplData->pluginUI.Initialize(m_argc, m_argv);
}

void World::LoadObjects()
{
	m_pImplData->m_pMainWindow = m_pImplData->pluginUI.GetMainWindow();
}

void World::Arguements(int argc, char ** argv)
{
	m_argc = argc;
	m_argv = argv;
}
