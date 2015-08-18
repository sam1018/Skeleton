#include "World.h"
#include "PluginsManager.h"
#include "../SkeletonInterface/IMainWindow.h"
#include "../SkeletonInterface/ICoreGUIApplication.h"

struct World::ImplData
{
	PluginsManager m_PluginsManager;
};

World::World() : 
	m_pImplData {std::make_unique<World::ImplData>()}
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

void World::InitializePlugins(int argc, char** argv)
{
	m_pImplData->m_PluginsManager.Initialize(argc, argv);
}

void World::Show()
{
	MW::Show();
}

int World::Run()
{
	return CGA::Run();
}
