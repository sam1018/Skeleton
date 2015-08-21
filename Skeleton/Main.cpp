#include <iostream>
#include "World.h"
#include <Windows.h>
#include <iostream>
#include "SkeletonSettings.h"

constexpr auto g_SettingsFile{ "../SkeletonSettings.xml" };

int main(int argc, char** argv)
{
	try
	{
		// Settings file must be loaded first
		// As later initializations depends on it
		SkeletonSettings::GetInstance().Load(g_SettingsFile);

		World::GetInstance().InitializePlugins(argc, argv);

		// Show the application
		World::GetInstance().Show();

		if (SkeletonSettings::GetInstance().m_bHideCmdPromptAfterInitialization)
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
