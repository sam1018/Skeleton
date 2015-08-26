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
	std::string pluginName;

	~PluginImpl()
	{
		FreeLibrary(hinstLib);
	}
};

void ThrowPluginLoadFailure(std::string pluginName)
{
	throw system_error(error_code(GetLastError(), system_category()), "Failed to load plugin: \"" + pluginName + "\". System Error");
}

void ThrowFunctionLoadFailure(std::string functionName)
{
	throw system_error(error_code(GetLastError(), system_category()), "Failed to load function: \"" + functionName + "\". System Error");
}

///////////////////////////////////////////////////////////////////////////////
/////////////          Plugin Definition                           ////////////
///////////////////////////////////////////////////////////////////////////////


Plugin::Plugin(std::string pluginName) :
	pluginImpl{ std::make_unique<PluginImpl>() }
{
	std::wstring fileName = StringToWString(pluginName);

	pluginImpl->hinstLib = LoadLibrary(fileName.c_str());

	if(!pluginImpl->hinstLib)
		ThrowPluginLoadFailure(pluginName);

	pluginImpl->pluginName = pluginName;

}


Plugin::~Plugin()
{
}

void* Plugin::GetFunctionAddress(std::string functionName)
{
	void* ret = GetProcAddress(pluginImpl->hinstLib, functionName.c_str());
	if (!ret)
		ThrowFunctionLoadFailure(functionName);

	return ret;
}

void Plugin::PluginInitialize(int argc, char** argv)
{
	bool ret = PluginCallerBody<bool, int, char**>(__func__, argc, argv);
	if (!ret)
	{
		std::exception e{ ("Initialization for plugin: \"" + pluginImpl->pluginName + "\" Failed.").c_str() };
		throw e;
	}
}

void Plugin::PluginDestroy()
{
	PluginCallerBody<void>(__func__);
}

std::string Plugin::GetPluginName()
{
	return pluginImpl->pluginName;
}
