#include "World.h"
#include "PluginUI.h"
#include "IMainFrame.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

namespace pt = boost::property_tree;

struct World::ImplData
{
	std::unique_ptr <IMainFrame> m_pMainFrame;
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
}

void World::LoadObjects()
{
	CreateMainFrame();
}

IMainFrame* World::CreateMainFrame()
{
	m_pImplData->m_pMainFrame = m_pImplData->pluginUI.CreateMainFrame();
	return m_pImplData->m_pMainFrame.get();
}
