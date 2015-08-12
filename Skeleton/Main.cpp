#include <iostream>
#include "World.h"
#include "Exceptions.h"
#include <Windows.h>

int main(int argc, char** argv)
{
	try
	{
		World::GetInstance().Arguements(argc, argv);
		World::GetInstance().LoadPlugins("PluginsList.xml");
		World::GetInstance().LoadObjects();
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
