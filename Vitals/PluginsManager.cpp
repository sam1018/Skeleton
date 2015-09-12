#include "Plugin.h"
#include "Routines.h"
#include "PluginsManager.h"
#include "CallerManager.h"
#include "UI/IOutputWindow.h"
#include "UI/IPluginExplorer.h"
#include "Vitals\IVitalsInterfaceManager.h"
#include <array>
#include <functional>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>


using namespace VT;
using namespace std;
using namespace Routines;


using PluginsArrayDynamic = vector<unique_ptr<Plugin>>;



struct PluginsManager::PluginsManagerImpl
{
	PluginsArrayDynamic pluginsArray;

	Plugin* GetPlugin(const string &pluginName)
	{
		for (auto &plugin : pluginsArray)
		{
			if (IsSamePath(plugin->GetPluginName(), pluginName))
				return plugin.get();
		}

		return nullptr;
	}

	Plugin* LoadPlugin(const string &pluginName)
	{
		Plugin *ret = GetPlugin(pluginName);
		if (ret)
			return ret;

		unique_ptr<Plugin> plugin{ make_unique<Plugin>(pluginName) };

		ret = plugin.get(); // store return result before moving

		pluginsArray.push_back(move(plugin));

		return ret;
	}
};


///////////////////////////////////////////////////////////////////////////////
/////////////          PluginsManager Definition                   ////////////
///////////////////////////////////////////////////////////////////////////////


PluginsManager::PluginsManager() :
	pluginsManagerImpl{ make_unique<PluginsManager::PluginsManagerImpl>() }
{
}

PluginsManager::~PluginsManager()
{
}

void PluginsManager::ExecuteFunction_(const string &pluginName, const string &functionName)
{
	Plugin *plugin = pluginsManagerImpl->GetPlugin(pluginName);

	if (plugin == nullptr)
		ThrowPluginLoadFailure(pluginName);

	function<void(void)> f = (void(*)(void))plugin->GetFunctionAddress(functionName);
	GetCallerManager()->RegisterCaller(CreateCaller(f, plugin), CallType::OneTime);
}

bool PluginsManager::IsPluginLoaded_(const std::string & pluginName)
{
	return pluginsManagerImpl->GetPlugin(pluginName) != nullptr;
}

IPlugin* PluginsManager::LoadPlugin_(const std::string & pluginName)
{
	return pluginsManagerImpl->LoadPlugin(pluginName);
}
