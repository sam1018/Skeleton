#include <iostream>
#include "World.h"
#include "Exceptions.h"
#include <Windows.h>
#include "Main.h"

int main(int argc, char** argv)
{
	try
	{
		// Initialize the world
		World::GetInstance().Arguements(argc, argv);
		World::GetInstance().LoadPlugins("PluginsList.xml");
		World::GetInstance().LoadObjects();

		// Show the application
		World::GetInstance().Show();

		// Run the application
		World::GetInstance().Run();
	}
	catch (PluginFailedException& e)
	{
		std::cerr << e.what() << "\n";
	}
	catch (...)
	{
		std::cerr << "Something went wrong!!! Closing application.\n";
	}
}
