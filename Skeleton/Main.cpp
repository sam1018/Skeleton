#include "World.h"
#include "Routines.h"
#include <iostream>
#include <Windows.h>

using namespace std;
using namespace Routines;


int main(int argc, char** argv)
{
	try
	{
		SetBinFilePath(argv[0]);

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
	}
	catch (exception &e)
	{
		cerr << e.what() << "\n";
	}
	catch (...)
	{
		cerr << "Something went wrong!!! Closing application.\n";
	}
}
