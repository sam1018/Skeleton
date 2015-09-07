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
	PluginsArrayDynamic pluginsArrayDynamic;
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
	Plugin *plugin = GetDynamicPlugin(pluginName);

	if (plugin == nullptr)
		ThrowPluginLoadFailure(pluginName);

	function<void(void)> f = (void(*)(void))plugin->GetFunctionAddress(functionName);
	GetCallerManager()->RegisterCaller(CreateCaller(f, plugin), CallType::OneTime);
}

Plugin* PluginsManager::GetDynamicPlugin(const string &pluginName)
{
	for (auto &plugin : pluginsManagerImpl->pluginsArrayDynamic)
	{
		if (IsSamePath(plugin->GetPluginName(), pluginName))
			return plugin.get();
	}

	unique_ptr<Plugin> plugin{ make_unique<Plugin>(pluginName) };

	Plugin *ret = plugin.get(); // store return result before moving
	pluginsManagerImpl->pluginsArrayDynamic.push_back(move(plugin));

	return ret;
}
