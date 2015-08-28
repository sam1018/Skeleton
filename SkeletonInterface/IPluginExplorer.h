#pragma once

#include "UIItem.h"
#include "SkeletonInterface.h"
#include <memory>
#include <vector>

namespace PE
{
	// Requirements for interface implementer
	//
	// Button control: To load plugin
	// Text = "Load Plugin", Click Function = "LoadPlugin"
	// Tree control: To display plugins and functions...
	// And, Item Double Click Handler Function = "ExecuteFunction"
	class SKELETONINTERFACE_DECLSPEC IPluginExplorer : public UI::UIItem
	{
	public:
		IPluginExplorer();
		virtual ~IPluginExplorer() = 0;

		void InitializeItem();
		void Cleanup();

		void LoadPlugin();
		void LoadPlugin(const std::string &pluginName, std::vector<std::string> &functions);
		virtual void AddPluginDataToTree(const std::string &pluginName, const std::vector<std::string> &functions) = 0;

		// Give the plugin name with full path and function name to execute
		void ExecuteFunction(const std::string &pluginName, const std::string &functionName);

	private:
		struct IPluginExplorerImpl;
		// We can safely ignore C4251 in this case
#pragma warning( push )
#pragma warning( disable : 4251 )
		std::unique_ptr<IPluginExplorerImpl> pluginExplorerImpl;
#pragma warning( pop ) 		
	};
}
