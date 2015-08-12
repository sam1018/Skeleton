#pragma once

#include <string>
#include <memory>

class IPlugin
{
public:
	IPlugin();
	virtual ~IPlugin() = 0;

	void LoadModule(std::string moduleName);

	void Initialize(int argc, char** argv);

protected:
	void* GetFunctionAddress(std::string functionName);

private:
	std::wstring GetModuleNameForWindows(std::string moduleName);

private:
	struct ImplData;
	std::unique_ptr <ImplData> m_pImplData;


	
	
	// Plugin caller body
	// Add new function if you need a caller with different parameter
	// Can variadic template solve this problem ? Need to study on this
public:
	template <typename RetType>
	RetType PluginCallerBody(std::string funcName)
	{
		using FuncType = RetType(*)(void);
		FuncType func = (FuncType)GetFunctionAddress(funcName);
		return func();
	}
};
