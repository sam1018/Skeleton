#include "World.h"
#include "Module.h"
#include "Routines.h"
#include "SkeletonSettings.h"
#include "UI/UIItem.h"
#include "UI/IMainWindow.h"
#include "UI/ICoreGUIApplication.h"
#include "UI/IUIInterfaceManager.h"
#include "Vitals/IPluginsManager.h"
#include "Vitals\IVitalsInterfaceManager.h"

struct World::WorldImpl
{
	const std::string settingsFile{ "SkeletonSettings.xml" };
	SkeletonSettings skeletonSettings{ Routines::GetSettingsFileFullPath_Load(settingsFile) };
	Module<UI::IUIInterfaceManager*> uiModule;
	Module<VT::IVitalsInterfaceManager*> vitalsModule;

	WorldImpl(int argc, char** argv) :
		uiModule{ skeletonSettings.uiModule, argc, argv },
		vitalsModule{ skeletonSettings.vitalsModule, argc, argv }
	{
		UI::SetUIInterfaceManager(uiModule.GetInterfaceManager());
		VT::SetVitalsInterfaceManager(vitalsModule.GetInterfaceManager());
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
	UI::InitializeItems();

	CGA::FinishInitialization();

	CGA::SetupFPS(worldImpl->skeletonSettings.fps);
}

void World::Show() const
{
	MW::Show();
}

int World::Run() const
{
	return CGA::Run();
}

void World::Cleanup() const
{
	UI::Cleanup();
}

bool World::IsHideCmdPromptAfterInitialization() const
{
	return worldImpl->skeletonSettings.hideCmdPromptAfterInitialization;
}
