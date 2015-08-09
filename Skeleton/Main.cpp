#include <iostream>
#include "World.h"
#include "Exceptions.h"

int main()
{
	try
	{
		World::GetInstance().LoadPlugins("PluginsList.xml");
		World::GetInstance().LoadObjects();
	}
	catch (FunctionLoadFailedException& e)
	{
		std::cerr << "ERROR!!!! Failed to load function: " << e.what() << "\n";
	}
	catch (ModuleLoadException& e)
	{
		std::cerr << "ERROR!!!! Failed to load module: " << e.what() << "\n";
	}
	catch (...)
	{
		std::cerr << "Something went wrong!!! Closing application.\n";
	}
}
