#include <vector>
#include <thread>
#include <iostream>
using namespace std;

extern "C" void __declspec(dllexport) TestFuncMsg()
{
	std::cout << "Function Call To TestFunc Succeeded.\n";
}

extern "C" void __declspec(dllexport) TestFuncRandNums()
{
	for (int i = 0; i < 15; i++)
		std::cout << i << " " << rand() << "\n";
}

void Msg()
{
	std::cout << "Fixed String. Will be run in threaded mode. Check for data corruption.\n";
}

extern "C" void __declspec(dllexport) TestFuncRandThreadedMsg()
{
	std::vector <std::thread> vt;

	for (int i = 0; i < 10; i++)
	{
		vt[i] = std::thread(Msg);
	}

	for (int i = 0; i < 10; i++)
		vt[i].join();
}



extern "C" void __declspec(dllexport) TestFunc10sSleep()
{
	std::cout << "Go to sleep\n";
	auto start = std::chrono::high_resolution_clock::now();
	std::this_thread::sleep_for(10s);
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, nano> duration = end - start;
	std::cout << "Sleep time: " << (end - start).count() << "ns\n";
}
