#include "World.h"
#include "Module.h"
#include "Routines.h"
#include "SkeletonSettings.h"
#include "UI/IMainWindow.h"
#include "UI/ICoreGUIApplication.h"
#include "UI/IUIInterfaceManager.h"
#include "Vitals/IPluginsManager.h"
#include "Vitals\IMessagePrinter.h"
#include "Vitals\IVitalsInterfaceManager.h"


using namespace UI;
using namespace VT;
using namespace std;
using namespace Routines;


struct World::WorldImpl
{
	const string settingsFile{ "SkeletonSettings.xml" };
	SkeletonSettings skeletonSettings{ GetSettingsFileFullPath_Load(settingsFile) };
	Module<IVitalsInterfaceManager*> vitalsModule;
	Module<IUIInterfaceManager*> uiModule;

	WorldImpl(int argc, char** argv)
	{
		vitalsModule.Initialize(skeletonSettings.vitalsModule, argc, argv);
		SetVitalsInterfaceManager(vitalsModule.GetInterfaceManager());

		uiModule.Initialize(skeletonSettings.uiModule, argc, argv);
		SetUIInterfaceManager(uiModule.GetInterfaceManager());
	}
};


///////////////////////////////////////////////////////////////////////////////
/////////////          World Definition                            ////////////
///////////////////////////////////////////////////////////////////////////////


World::World(int argc, char** argv) :
	worldImpl{ make_unique<WorldImpl>(argc, argv) }
{
	Initialize();
}

World::~World()
{
}

void World::Initialize() const
{
	GetMessagePrinter()->SetOutputWindow(GetOutputWindow());

	ICoreGUIApplication *cga = GetCoreGUIApplication();
	cga->FinishInitialization();
	cga->SetupFPS(worldImpl->skeletonSettings.fps);
}

void World::Show() const
{
	GetMainWindow()->Show();
}

int World::Run() const
{
	return GetCoreGUIApplication()->Run();
}

bool World::IsHideCmdPromptAfterInitialization() const
{
	return worldImpl->skeletonSettings.hideCmdPromptAfterInitialization;
}
