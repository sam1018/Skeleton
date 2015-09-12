#pragma once

#include "SkeletonInterface.h"
#include <memory>
#include <vector>

namespace UI
{
	// Requirements for interface implementer
	//
	// Button control: To load plugin
	// Text = "Load Plugin", Click Function = "LoadPlugin"
	// Tree control: To display plugins and functions...
	// And, Item Double Click Handler Function = "ExecuteFunction"
	class SKELETONINTERFACE_DECLSPEC IPluginExplorer
	{
	public:
		IPluginExplorer();
		virtual ~IPluginExplorer() = 0;

		void LoadPlugin();

		// Give the plugin name with full path and function name to execute
		void ExecuteFunction(const std::string &pluginName, const std::string &functionName);

		void* GetControlImplementationSpecific();

		void AddPluginDataToTree(const std::string &pluginName,
			const std::vector<std::string> &functions);

	private:
		virtual void* GetControlImplementationSpecific_() = 0;
		virtual void AddPluginDataToTree_(const std::string &pluginName, 
			const std::vector<std::string> &functions) = 0;
	};
}
