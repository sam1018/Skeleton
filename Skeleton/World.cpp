#include "World.h"
#include "Module.h"
#include "Routines.h"
#include "SkeletonSettings.h"
#include "UI/IMainWindow.h"
#include "UI/ICoreGUIApplication.h"
#include "UI/IUIInterfaceManager.h"
#include "Vitals/IPluginsManager.h"
#include "Vitals\IVitalsInterfaceManager.h"

struct World::WorldImpl
{
	const std::string settingsFile{ "SkeletonSettings.xml" };
	SkeletonSettings skeletonSettings{ Routines::GetSettingsFileFullPath_Load(settingsFile) };
	Module<VT::IVitalsInterfaceManager*> vitalsModule;
	Module<UI::IUIInterfaceManager*> uiModule;

	WorldImpl(int argc, char** argv)
	{
		vitalsModule.Initialize(skeletonSettings.vitalsModule, argc, argv);
		VT::SetVitalsInterfaceManager(vitalsModule.GetInterfaceManager());

		uiModule.Initialize(skeletonSettings.uiModule, argc, argv);
		UI::SetUIInterfaceManager(uiModule.GetInterfaceManager());
	}
};


///////////////////////////////////////////////////////////////////////////////
/////////////          World Definition                            ////////////
///////////////////////////////////////////////////////////////////////////////


World::World(int argc, char** argv) :
	worldImpl{ std::make_unique<WorldImpl>(argc, argv) }
{
	Initialize();
}

World::~World()
{
}

void World::Initialize() const
{
	//UI::InitializeItems();

	UI::ICoreGUIApplication *cga = UI::GetCoreGUIApplication();

	cga->FinishInitialization();

	cga->SetupFPS(worldImpl->skeletonSettings.fps);
}

void World::Show() const
{
	UI::GetMainWindow()->Show();
}

int World::Run() const
{
	return UI::GetCoreGUIApplication()->Run();
}

void World::Cleanup() const
{
	//UI::Cleanup();
}

bool World::IsHideCmdPromptAfterInitialization() const
{
	return worldImpl->skeletonSettings.hideCmdPromptAfterInitialization;
}
