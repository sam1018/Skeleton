#include "World.h"
#include "../SkeletonInterface/UIItem.h"
#include "../SkeletonInterface/IMainWindow.h"
#include "../SkeletonInterface/PluginsManager.h"
#include "../SkeletonInterface/ICoreGUIApplication.h"


///////////////////////////////////////////////////////////////////////////////
/////////////          World Definition                            ////////////
///////////////////////////////////////////////////////////////////////////////


World::World()
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
	PluginsManager::GetInstance().Initialize(argc, argv);

	UI::InitializeItems();
}

void World::Show()
{
	MW::Show();
}

int World::Run()
{
	return CGA::Run();
}

void World::Cleanup()
{
	UI::Cleanup();
	PluginsManager::GetInstance().Destroy();
}
