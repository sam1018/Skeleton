#include "Routines.h"
#include "UI/IPluginExplorer.h"
#include "UI/ICommonControls.h"
#include "UI\IUIInterfaceManager.h"
#include <Vitals\IPlugin.h>
#include "Vitals\IMessagePrinter.h"
#include "Vitals/IPluginsManager.h"
#include "Vitals\IVitalsInterfaceManager.h"
#include <iostream>


using namespace UI;
using namespace VT;
using namespace std;
using namespace Routines;



IPluginExplorer::IPluginExplorer()
{
}

IPluginExplorer::~IPluginExplorer()
{
}

void IPluginExplorer::LoadPlugin()
{
	string pluginName = GetCommonControls()->GetOpenFileName(
		GetControlImplementationSpecific(), "Open As", 
		GetBinDirectory(), ("dll Files (*.dll)"));

	if (pluginName == "")
		return;

	IPluginsManager *pm = GetPluginsManager();

	if (pm->IsPluginLoaded(pluginName))
	{
		PRINT_MESSAGE(MsgCat_PluginExplorer, "Plugin already loaded.\n", true, true);
		return;
	}

	IPlugin *plugin = pm->LoadPlugin(pluginName);

	if (!plugin)
	{
		PRINT_MESSAGE(MsgCat_PluginExplorer, "Failed to load plugin.\n", true, true);
		return;
	}

	vector<string> functions = plugin->GetFunctions();

	AddPluginDataToTree(pluginName, functions);
}

void IPluginExplorer::ExecuteFunction(const string &pluginName, const string &functionName)
{
	auto success{ true };

	try
	{
		GetPluginsManager()->ExecuteFunction(pluginName, functionName);
	}
	catch (exception &e)
	{
		success = false;
		PRINT_MESSAGE(MsgCat_PluginExplorer, e.what(), true, true)
	}

	if (success)
		PRINT_MESSAGE(MsgCat_PluginExplorer, "Queued function: " + functionName + "\n", true, true)
}

void IPluginExplorer::AddPluginDataToTree(const string &pluginName,
	const vector<string> &functions)
{
	AddPluginDataToTree_(pluginName, functions);
}

void* IPluginExplorer::GetControlImplementationSpecific()
{
	return GetControlImplementationSpecific_();
}
