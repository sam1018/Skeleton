#include "World.h"
#include "SkeletonSettings.h"
#include "../SkeletonInterface/Routines.h"
#include <iostream>
#include <Windows.h>


constexpr auto settingsFile{ "SkeletonSettings.xml" };


int main(int argc, char** argv)
{
	try
	{
		Routines::SetBinFilePath(argv[0]);

		// Settings file must be loaded first
		// As later initializations depends on it
		SkeletonSettings::GetInstance().Load(Routines::GetSettingsFileFullPath_Load(settingsFile));

		World::GetInstance().InitializePlugins(argc, argv);

		// Show the application
		World::GetInstance().Show();

		if (SkeletonSettings::GetInstance().hideCmdPromptAfterInitialization)
		{
			HWND hwnd = GetConsoleWindow();
			ShowWindow(hwnd, 0);
		}

		// Run the application
		World::GetInstance().Run();

		// Application finished... Cleanup Time
		World::GetInstance().Cleanup();
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << "\n";
	}
	catch (...)
	{
		std::cerr << "Something went wrong!!! Closing application.\n";
	}
}
