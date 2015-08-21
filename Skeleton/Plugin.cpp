#include "Plugin.h"
#include <functional>
#include <windows.h> 
#include <boost\system\error_code.hpp>
#include <boost\system\system_error.hpp>

using namespace boost::system;

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

struct Plugin::PluginImpl
{
	HINSTANCE hinstLib = nullptr;
	std::string moduleName;

	~PluginImpl()
	{
		FreeLibrary(hinstLib);
	}
};

void ThrowSystemError(std::string msg)
{
	throw system_error(error_code(GetLastError(), system_category()), msg);
}


///////////////////////////////////////////////////////////////////////////////
/////////////          Plugin Definition                           ////////////
///////////////////////////////////////////////////////////////////////////////


Plugin::Plugin(std::string moduleName) :
	pluginImpl{ std::make_unique<PluginImpl>() }
{
	std::wstring fileName = GetModuleNameForWindows(moduleName);

	pluginImpl->hinstLib = LoadLibrary(fileName.c_str());

	if(!pluginImpl->hinstLib)
		ThrowSystemError(moduleName);
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
	if (!ret)
		ThrowSystemError(functionName);

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
