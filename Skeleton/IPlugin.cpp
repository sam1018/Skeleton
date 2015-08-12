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

std::string GetErrorMsg(LPCTSTR lpszFunction)
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
		(lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
	StringCchPrintf((LPTSTR)lpDisplayBuf,
		LocalSize(lpDisplayBuf) / sizeof(TCHAR),
		TEXT("ERROR!!! %s failed with error %d: %s"),
		lpszFunction, dw, lpMsgBuf);

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
}

void IPlugin::LoadModule(std::string moduleName)
{
	std::wstring fileName = GetModuleNameForWindows(moduleName);
	m_pImplData->hinstLib = LoadLibrary(fileName.c_str());

	if (!m_pImplData->hinstLib)
	{
		PluginFailedException ob{ GetErrorMsg(fileName.c_str()).c_str() };
		throw ob;
	}
}

void* IPlugin::GetFunctionAddress(std::string functionName)
{
	void* ret = GetProcAddress(m_pImplData->hinstLib, functionName.c_str());

	if (!ret)
	{
		PluginFailedException ob { (GetErrorMsg(StringToWString(functionName).c_str())).c_str()};
		throw ob;
	}

	return ret;
}

void IPlugin::Initialize(int argc, char** argv)
{
	void* p = GetFunctionAddress("PluginInitialize");
	InitFunc Func = (InitFunc) GetFunctionAddress("PluginInitialize");
	if (Func)
		Func(argc, argv);
}

std::wstring IPlugin::GetModuleNameForWindows(std::string moduleName)
{
	return StringToWString(moduleName + ".dll");
}
