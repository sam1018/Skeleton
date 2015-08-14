#include "IPlugin.h"
#include <windows.h> 
#include "Exceptions.h"
#include <functional>
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

	std::wstring ret((LPTSTR)lpDisplayBuf );

	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);

	return WStringToString(ret);
}

struct IPlugin::ImplData
{
	HINSTANCE hinstLib = nullptr;

	~ImplData()
	{
		FreeLibrary(hinstLib);
	}
};

IPlugin::IPlugin() : m_pImplData{std::make_unique<ImplData>()}
{
}


IPlugin::~IPlugin()
{
	PluginDestroy();
}

void IPlugin::LoadModule(std::string moduleName)
{
	std::wstring fileName = GetModuleNameForWindows(moduleName);
	m_pImplData->hinstLib = LoadLibrary(fileName.c_str());
	std::wstring errDesc = L"Loading module: \"" + fileName + L"\" failed";

	if (!m_pImplData->hinstLib)
	{
		PluginFailedException ob{ GetErrorMsg(errDesc.c_str()).c_str() };
		throw ob;
	}
}

void* IPlugin::GetFunctionAddress(std::string functionName)
{
	void* ret = GetProcAddress(m_pImplData->hinstLib, functionName.c_str());
	std::wstring errDesc = L"Loading function: \"" + StringToWString(functionName) + L"\" failed";

	if (!ret)
	{
		PluginFailedException ob { (GetErrorMsg(errDesc.c_str())).c_str()};
		throw ob;
	}

	return ret;
}

void IPlugin::PluginInitialize(int argc, char** argv)
{
	PluginCallerBody<void, int, char**>(__func__, argc, argv);
}

void IPlugin::PluginDestroy()
{
	PluginCallerBody<void>(__func__);
}

std::wstring IPlugin::GetModuleNameForWindows(std::string moduleName)
{
	return StringToWString(moduleName + ".dll");
}
