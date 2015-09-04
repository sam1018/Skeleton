#pragma once

#include <string>

namespace VT
{
	class IPluginsManager
	{
	public:
		void ExecuteFunctionDynamic(std::string pluginName, std::string functionName);

	private:
		virtual void ExecuteFunctionDynamic_(std::string pluginName, std::string functionName) = 0;
	};
}
