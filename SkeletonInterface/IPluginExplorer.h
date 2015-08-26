#pragma once

#include "UIItem.h"
#include "SkeletonInterface.h"
#include <memory>
#include <vector>

namespace PE
{
	class SKELETONINTERFACE_DECLSPEC IPluginExplorer : public UI::UIItem
	{
	public:
		IPluginExplorer();
		virtual ~IPluginExplorer() = 0;

		void InitializeItem();
		void Cleanup();

		void LoadPlugin(std::string pluginName, std::vector<std::string>& functions);
		void ExecuteFunction(std::string pluginName, std::string functionName);

	private:
		struct IPluginExplorerImpl;
		// We can safely ignore C4251 in this case
#pragma warning( push )
#pragma warning( disable : 4251 )
		std::unique_ptr<IPluginExplorerImpl> pluginExplorerImpl;
#pragma warning( pop ) 		
	};
}
