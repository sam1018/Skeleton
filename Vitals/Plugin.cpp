#include "Plugin.h"
#include "CallerManager.h"
#include "Vitals\IVitalsInterfaceManager.h"
#include <system_error>
#include <windows.h> 

#pragma warning( push )
#pragma warning( disable : 4091 )
#include <Imagehlp.h>
#pragma warning( pop )


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


vector<string> ListDLLFunctions(string sADllName)
{
	vector<string> slListOfDllFunctions;
	unsigned long cDirSize;
	_LOADED_IMAGE LoadedImage;
	string sName;
	slListOfDllFunctions.clear();
	if (MapAndLoad(sADllName.c_str(), NULL, &LoadedImage, TRUE, TRUE))
	{
		_IMAGE_EXPORT_DIRECTORY *ImageExportDirectory = (_IMAGE_EXPORT_DIRECTORY*)
			ImageDirectoryEntryToData(LoadedImage.MappedAddress,
				false, IMAGE_DIRECTORY_ENTRY_EXPORT, &cDirSize);
		if (ImageExportDirectory != NULL)
		{
			DWORD *dNameRVAs = (DWORD *)ImageRvaToVa(LoadedImage.FileHeader,
				LoadedImage.MappedAddress,
				ImageExportDirectory->AddressOfNames, NULL);
			for (size_t i = 0; i < ImageExportDirectory->NumberOfNames; i++)
			{
				sName = (char *)ImageRvaToVa(LoadedImage.FileHeader,
					LoadedImage.MappedAddress,
					dNameRVAs[i], NULL);
				slListOfDllFunctions.push_back(sName);
			}
		}
		UnMapAndLoad(&LoadedImage);
	}

	return slListOfDllFunctions;
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

vector<string> Plugin::GetFunctions_()
{
	return ListDLLFunctions(pluginImpl->pluginName);
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
