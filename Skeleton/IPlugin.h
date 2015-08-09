#pragma once

#include <string>
#include <memory>

class IPlugin
{
public:
	IPlugin();
	virtual ~IPlugin() = 0;

	void LoadModule(std::string moduleName);

	void* GetFunctionAddress(std::string functionName);

private:
	std::wstring GetModuleNameForWindows(std::string moduleName);

private:
	struct ImplData;
	std::unique_ptr <ImplData> m_pImplData;
};
