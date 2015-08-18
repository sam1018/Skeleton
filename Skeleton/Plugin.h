#pragma once

#include <string>
#include <memory>

class Plugin
{
public:
	Plugin(std::string moduleName);
	~Plugin();

	void PluginInitialize(int argc, char** argv);

	void PluginDestroy();

	// Purpose: Calls "funcName" function, that's residing within the plugin
	// Precaution: "funcName" must have "C" linkage
	// Parameter funcName: Name of the function that will be called
	// Template argument : RetType: return value of "funcName" function
	//                     Args: arguments for "funcName" function
	template <typename RetType, class... ArgsType>
	RetType PluginCallerBody(std::string funcName, ArgsType... args)
	{
		using FuncType = RetType(*)(ArgsType...);
		FuncType func = (FuncType)GetFunctionAddress(funcName);
		return func(std::forward<ArgsType>(args)...);
	}

protected:
	void* GetFunctionAddress(std::string functionName);

private:
	std::wstring GetModuleNameForWindows(std::string moduleName);

private:
	struct ImplData;
	std::unique_ptr <ImplData> m_pImplData;
};
