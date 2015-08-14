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

	// Purpose: Calls "funcName" function, that's residing within the plugin
	// Precaution: "funcName" must have "C" linkage
	// Parameter funcName: Name of the function that will be called
	// Template argument : RetType: return value of "funcName" function
	//                     Args: arguments for "funcName" function
	template <typename RetType, class... Args>
	RetType PluginCallerBody(std::string funcName)
	{
		using FuncType = RetType(*)(void);
		FuncType func = (FuncType)GetFunctionAddress(funcName);
		return func(std::forward<Args>(_Args)...);
	}

protected:
	void* GetFunctionAddress(std::string functionName);

private:
	std::wstring GetModuleNameForWindows(std::string moduleName);

private:
	struct ImplData;
	std::unique_ptr <ImplData> m_pImplData;
};
