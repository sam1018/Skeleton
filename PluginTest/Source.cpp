#include <vector>
#include <thread>
#include <iostream>

using namespace std;

extern "C" void __declspec(dllexport) TestFuncMsg()
{
	cout << "Function Call To TestFunc Succeeded.\n";
}

extern "C" void __declspec(dllexport) TestFuncRandNums()
{
	for (int i = 0; i < 10; i++)
		cout << rand() << " " << rand() << "\n";
}

extern "C" void __declspec(dllexport) TestFuncRandNumsInfinite()
{
	for (;;)
		cout << rand() << " " << rand() << "\n";
}

void Msg()
{
	cout << "Fixed String. Will be run in multi threaded mode. Check for data corruption.\n";
}

extern "C" void __declspec(dllexport) TestFuncRandThreadedMsg()
{
	vector <thread> vt;

	for (int i = 0; i < 10; i++)
	{
		vt.push_back(thread(Msg));
	}

	for (int i = 0; i < 10; i++)
		vt[i].join();
}



extern "C" void __declspec(dllexport) TestFunc10sSleep()
{
	cout << "Go to sleep\n";
	auto start = chrono::high_resolution_clock::now();
	this_thread::sleep_for(10s);
	auto end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration<double, nano>(end - start);
	cout << "Sleep time: " << duration.count() << "ns\n";
}

extern "C" void __declspec(dllexport) TestFunc2Plus5()
{
	cout << 2 + 5 << "\n";
}

#include <windows.h>
#include <gl\GL.h>

extern "C" void __declspec(dllexport) TestFuncOpenGlSetBackColor()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(1, 0, 0, 1);
	glFrontFace(GL_CW);
	glCullFace(GL_FRONT);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
}
