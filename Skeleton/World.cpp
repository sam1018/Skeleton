#include "World.h"
#include "PluginsManager.h"
#include "../SkeletonInterface/IMainWindow.h"
#include "../SkeletonInterface/ICoreGUIApplication.h"

struct World::WorldImpl
{
	PluginsManager pluginsManager;
};


///////////////////////////////////////////////////////////////////////////////
/////////////          World Definition                            ////////////
///////////////////////////////////////////////////////////////////////////////


World::World() :
	worldImpl{ std::make_unique<World::WorldImpl>() }
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
	worldImpl->pluginsManager.Initialize(argc, argv);
}

void World::Show()
{
	GUI::Show();
}

int World::Run()
{
	return GUI::Run();
}
