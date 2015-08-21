#include "Plugin.h"
#include <functional>
#include <windows.h> 
#include <strsafe.h>

typedef int(*InitFunc)(int argc, char** argv);

std::wstring StringToWString(std::string src)
{
	std::wstring dest;
	dest.insert(dest.begin(), src.begin(), src.end());
	return dest;
}

std::string WStringToString(std::wstring src)
{
	std::string dest;
	dest.insert(dest.begin(), src.begin(), src.end());
	return dest;
}

std::string GetErrorMsg(LPCTSTR errDesc)
{
	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;
	DWORD dw = GetLastError();

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0, NULL);

	// Display the error message and exit the process

	lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
		(lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)errDesc) + 40) * sizeof(TCHAR));
	StringCchPrintf((LPTSTR)lpDisplayBuf,
		LocalSize(lpDisplayBuf) / sizeof(TCHAR),
		TEXT("ERROR!!! %s !!! Last error code %d: %s"),
		errDesc, dw, lpMsgBuf);

	std::wstring ret((LPTSTR)lpDisplayBuf);

	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);

	return WStringToString(ret);
}

struct Plugin::PluginImpl
{
	HINSTANCE hinstLib = nullptr;
	std::string moduleName;

	~PluginImpl()
	{
		FreeLibrary(hinstLib);
	}
};


///////////////////////////////////////////////////////////////////////////////
/////////////          Plugin Definition                           ////////////
///////////////////////////////////////////////////////////////////////////////


Plugin::Plugin(std::string moduleName) :
	pluginImpl{ std::make_unique<PluginImpl>() }
{
	std::wstring fileName = GetModuleNameForWindows(moduleName);
	pluginImpl->hinstLib = LoadLibrary(fileName.c_str());
	pluginImpl->moduleName = moduleName;
	std::wstring errDesc = L"Loading module: \"" + fileName + L"\" failed";

	if (!pluginImpl->hinstLib)
	{
		std::exception e{ GetErrorMsg(errDesc.c_str()).c_str() };
		throw e;
	}
}


Plugin::~Plugin()
{
	// Eat up, if PluginDestroy() throws
	try
	{
		PluginDestroy();
	}
	catch (...) {}
}

void* Plugin::GetFunctionAddress(std::string functionName)
{
	void* ret = GetProcAddress(pluginImpl->hinstLib, functionName.c_str());
	std::wstring errDesc = L"Loading function: \"" + StringToWString(functionName) + L"\" failed";

	if (!ret)
	{
		std::exception e{ (GetErrorMsg(errDesc.c_str())).c_str() };
		throw e;
	}

	return ret;
}

void Plugin::PluginInitialize(int argc, char** argv)
{
	bool ret = PluginCallerBody<bool, int, char**>(__func__, argc, argv);

	if (!ret)
	{
		std::exception e{ ("Initialization for plugin: \"" + pluginImpl->moduleName + "\" Failed.").c_str() };
		throw e;
	}
}

void Plugin::PluginDestroy()
{
	PluginCallerBody<void>(__func__);
}

std::wstring Plugin::GetModuleNameForWindows(std::string moduleName)
{
	return StringToWString(moduleName + ".dll");
}
