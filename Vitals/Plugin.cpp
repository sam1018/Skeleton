#include "Plugin.h"
#include "CallerManager.h"
#include "Vitals\IVitalsInterfaceManager.h"
#include <system_error>
#include <windows.h> 


using namespace VT;
using namespace std;


typedef int(*InitFunc)(int argc, char** argv);


wstring StringToWString(string src)
{
	wstring dest;
	dest.insert(dest.begin(), src.begin(), src.end());
	return dest;
}

string WStringToString(wstring src)
{
	string dest;
	dest.insert(dest.begin(), src.begin(), src.end());
	return dest;
}

struct Plugin::PluginImpl
{
	HINSTANCE hinstLib = nullptr;
	string pluginName;

	~PluginImpl()
	{
		FreeLibrary(hinstLib);
	}
};

void ThrowPluginLoadFailure(string pluginName)
{
	throw system_error(error_code(GetLastError(), system_category()), "Failed to load plugin: \"" + pluginName + "\". System Error");
}

void ThrowFunctionLoadFailure(string functionName)
{
	throw system_error(error_code(GetLastError(), system_category()), "Failed to load function: \"" + functionName + "\". System Error");
}

///////////////////////////////////////////////////////////////////////////////
/////////////          Plugin Definition                           ////////////
///////////////////////////////////////////////////////////////////////////////


Plugin::Plugin(string pluginName) :
	pluginImpl{ make_unique<PluginImpl>() }
{
	wstring fileName = StringToWString(pluginName);

	pluginImpl->hinstLib = LoadLibrary(fileName.c_str());

	if(!pluginImpl->hinstLib)
		ThrowPluginLoadFailure(pluginName);

	pluginImpl->pluginName = pluginName;
}


Plugin::~Plugin()
{
	GetCallerManager()->PluginUnloaded(this);
}

void* Plugin::GetFunctionAddress(string functionName)
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
		exception e{ ("Initialization for plugin: \"" + pluginImpl->pluginName + "\" Failed.").c_str() };
		throw e;
	}
}

void Plugin::PluginDestroy()
{
	PluginCallerBody<void>(__func__);
}

string Plugin::GetPluginName()
{
	return pluginImpl->pluginName;
}
