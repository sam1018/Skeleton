#pragma once


#include <memory>
#include <string>
#include "Vitals\IPluginsManager.h"


class PluginsManager : public VT::IPluginsManager
{
public:
	PluginsManager();
	~PluginsManager();

private:
	virtual void ExecuteFunction_(const std::string &pluginName, const std::string &functionName);
	virtual bool IsPluginLoaded_(const std::string &pluginName);
	virtual VT::IPlugin* LoadPlugin_(const std::string &pluginName);

private:
	struct PluginsManagerImpl;
	// We can safely ignore C4251 in this case
#pragma warning( push )
#pragma warning( disable : 4251 )
	std::unique_ptr <PluginsManagerImpl> pluginsManagerImpl;
#pragma warning( pop )
};
