#include "IPlugin.h"
#include <windows.h> 
#include "Exceptions.h"

struct IPlugin::ImplData
{
	HINSTANCE hinstLib = nullptr;

	~ImplData()
	{
		FreeLibrary(hinstLib);
	}
};

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

IPlugin::IPlugin() : m_pImplData{std::make_unique<ImplData>()}
{
}


IPlugin::~IPlugin()
{
}

void IPlugin::LoadModule(std::string moduleName)
{
	std::wstring fileName = GetModuleNameForWindows(moduleName);
	m_pImplData->hinstLib = LoadLibrary(fileName.c_str());

	if (!m_pImplData->hinstLib)
	{
		ModuleLoadException ob{ WStringToString(fileName).c_str() };
		throw ob;
	}
}

void* IPlugin::GetFunctionAddress(std::string functionName)
{
	void* ret = GetProcAddress(m_pImplData->hinstLib, functionName.c_str());

	if (!ret)
	{
		FunctionLoadFailedException ob {functionName.c_str()};
		throw ob;
	}

	return ret;
}

std::wstring IPlugin::GetModuleNameForWindows(std::string moduleName)
{
	return StringToWString(moduleName + ".dll");
}
