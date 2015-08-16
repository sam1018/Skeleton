#include "World.h"
#include "PluginUI.h"
#include "../SkeletonInterface/IMainWindow.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

struct World::ImplData
{
	IMainWindow *m_pMainWindow;
	IOpenGLWindow *m_pIOpenGLWindow;
	PluginUI m_pluginUI;
	bool m_bHideCmdPrompt;

	struct Settings
	{
		std::string m_UIPluginName;
		bool m_bHideCmdPromptAfterInitialization;

		void Load(std::string fileName)
		{
			namespace pt = boost::property_tree;
			pt::ptree tree;
			pt::read_xml(fileName, tree);

			m_UIPluginName = tree.get("SkeletonSettings.PluginsList.UIPlugin", "QTUI");
			m_bHideCmdPromptAfterInitialization = tree.get("SkeletonSettings.HideCmdPromptAfterInitialization", false);
		}
	} m_Settings;
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

void World::LoadSettings(std::string fileName)
{
	m_pImplData->m_Settings.Load(fileName);
}

void World::LoadPlugins()
{
	m_pImplData->m_pluginUI.LoadModule(m_pImplData->m_Settings.m_UIPluginName);
	m_pImplData->m_pluginUI.PluginInitialize(m_argc, m_argv);
}

void World::LoadObjects()
{
	m_pImplData->m_pMainWindow = m_pImplData->m_pluginUI.GetMainWindow();
	m_pImplData->m_pIOpenGLWindow = m_pImplData->m_pluginUI.GetOpenGLWindow();
}

void World::Arguements(int argc, char ** argv)
{
	m_argc = argc;
	m_argv = argv;
}

void World::Show()
{
	m_pImplData->m_pMainWindow->Show();
}

int World::Run()
{
	return m_pImplData->m_pluginUI.Run();
}

bool World::HideCmdPromptAfterInitialization()
{
	return m_pImplData->m_Settings.m_bHideCmdPromptAfterInitialization;
}
