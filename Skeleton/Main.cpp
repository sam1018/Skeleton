#include <iostream>
#include "World.h"
#include <Windows.h>
#include "Main.h"

int main(int argc, char** argv)
{
	try
	{
		// Initialize the world
		World::GetInstance().Arguements(argc, argv);
		World::GetInstance().LoadPlugins("../PluginsList.xml");
		World::GetInstance().LoadObjects();

		// Show the application
		World::GetInstance().Show();

		HWND hwnd = GetConsoleWindow();
		ShowWindow(hwnd, 0);

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
