#include "Routines.h"
#include "Vitals\IMessagePrinter.h"
#include "Vitals\IVitalsInterfaceManager.h"
#include "Vitals/IPluginsManager.h"
#include "UI/IPluginExplorer.h"
#include "UI/ICommonControls.h"
#include "UI\IUIInterfaceManager.h"
#include <iostream>


using namespace UI;
using namespace VT;
using namespace std;
using namespace Routines;


void ListDLLFunctions(string sADllName, vector<string>& slListOfDllFunctions);


IPluginExplorer::IPluginExplorer()
{
}

IPluginExplorer::~IPluginExplorer()
{
}

void IPluginExplorer::LoadPlugin(const string &pluginName, vector<string> &functions)
{
	if (pluginName == "")
		return;

	// Clear the output window
	PRINT_MESSAGE(MsgCat_PluginExplorer, "", false, false)
	PRINT_MESSAGE(MsgCat_PluginExplorer, "Searching module for exported functions............... ", true, true)

	ListDLLFunctions(pluginName, functions);
	if (functions.empty())
		PRINT_MESSAGE(MsgCat_PluginExplorer, "No exported functions found.", true, true)
	else
		PRINT_MESSAGE(MsgCat_PluginExplorer, to_string(functions.size()) + " exported functions found.\n", true, true)
}

void IPluginExplorer::LoadPlugin()
{
	string pluginName = GetCommonControls()->GetOpenFileName(
		GetControlImplementationSpecific(), "Open As", 
		GetBinDirectory(), ("dll Files (*.dll)"));

	vector<string> functions;
	LoadPlugin(pluginName, functions);
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





#include <Windows.h>

// I hate warnings
#pragma warning( push )
#pragma warning( disable : 4091 )
#include <Imagehlp.h>
#pragma warning( pop )

void ListDLLFunctions(string sADllName, vector<string>& slListOfDllFunctions)
{
	unsigned long cDirSize;
	_LOADED_IMAGE LoadedImage;
	string sName;
	slListOfDllFunctions.clear();
	if (MapAndLoad(sADllName.c_str(), NULL, &LoadedImage, TRUE, TRUE))
	{
		_IMAGE_EXPORT_DIRECTORY *ImageExportDirectory = (_IMAGE_EXPORT_DIRECTORY*)
			ImageDirectoryEntryToData(LoadedImage.MappedAddress,
				false, IMAGE_DIRECTORY_ENTRY_EXPORT, &cDirSize);
		if (ImageExportDirectory != NULL)
		{
			DWORD *dNameRVAs = (DWORD *)ImageRvaToVa(LoadedImage.FileHeader,
				LoadedImage.MappedAddress,
				ImageExportDirectory->AddressOfNames, NULL);
			for (size_t i = 0; i < ImageExportDirectory->NumberOfNames; i++)
			{
				sName = (char *)ImageRvaToVa(LoadedImage.FileHeader,
					LoadedImage.MappedAddress,
					dNameRVAs[i], NULL);
				slListOfDllFunctions.push_back(sName);
			}
		}
		UnMapAndLoad(&LoadedImage);
	}
}
