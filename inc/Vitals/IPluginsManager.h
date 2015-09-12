#pragma once

#include <string>
#include <vector>

namespace VT
{
	class IPlugin;

	class IPluginsManager
	{
	public:
		void ExecuteFunction(const std::string &pluginName, const std::string &functionName);
		bool IsPluginLoaded(const std::string &pluginName);
		IPlugin* LoadPlugin(const std::string &pluginName);

	private:
		virtual void ExecuteFunction_(const std::string &pluginName, const std::string &functionName) = 0;
		virtual bool IsPluginLoaded_(const std::string &pluginName) = 0;
		virtual IPlugin* LoadPlugin_(const std::string &pluginName) = 0;
	};
}
