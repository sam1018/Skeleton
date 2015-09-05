#pragma once

#include <string>

namespace VT
{
	class IPluginsManager
	{
	public:
		void ExecuteFunction(const std::string &pluginName, const std::string &functionName);

	private:
		virtual void ExecuteFunction_(const std::string &pluginName, const std::string &functionName) = 0;
	};
}
