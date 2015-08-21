#include "World.h"
#include "SkeletonSettings.h"
#include <iostream>
#include <Windows.h>


constexpr auto settingsFile{ "../SkeletonSettings.xml" };


int main(int argc, char** argv)
{
	try
	{
		// Settings file must be loaded first
		// As later initializations depends on it
		SkeletonSettings::GetInstance().Load(settingsFile);

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
