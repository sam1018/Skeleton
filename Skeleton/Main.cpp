#include "World.h"
#include "Routines.h"
#include <iostream>
#include <Windows.h>


int main(int argc, char** argv)
{
	try
	{
		Routines::SetBinFilePath(argv[0]);

		World world(argc, argv);

		// Show the application
		world.Show();

		if (world.IsHideCmdPromptAfterInitialization())
		{
			HWND hwnd = GetConsoleWindow();
			ShowWindow(hwnd, 0);
		}

		// Run the application
		world.Run();

		// Application finished... Cleanup Time
		world.Cleanup();
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
