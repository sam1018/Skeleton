#include "World.h"
#include "SkeletonSettings.h"
#include "../SkeletonInterface/UIItem.h"
#include "../SkeletonInterface/IMainWindow.h"
#include "../SkeletonInterface/PluginsManager.h"
#include "../SkeletonInterface/FunctionManager.h"
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

	CGA::FinishInitialization();

	CGA::SetupFPS(SkeletonSettings::GetInstance().fps);
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
