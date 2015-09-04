#pragma once

#include "Vitals\IPlugin.h"
#include <string>
#include <memory>
#include <functional>

void ThrowPluginLoadFailure(std::string pluginName);
void ThrowFunctionLoadFailure(std::string functionName);

class Plugin : public VT::IPlugin
{
public:
	explicit Plugin(std::string pluginName);
	~Plugin();

	void PluginInitialize(int argc, char** argv);

	void PluginDestroy();

	std::string GetPluginName();

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

		if (!func)
			ThrowFunctionLoadFailure(funcName);

		return func(std::forward<ArgsType>(args)...);
	}

	void* GetFunctionAddress(std::string functionName);

private:
	struct PluginImpl;
	std::unique_ptr <PluginImpl> pluginImpl;
};
