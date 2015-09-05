#include "Routines.h"
#include "Vitals\IMessagePrinter.h"
#include "Vitals\IVitalsInterfaceManager.h"
#include "Vitals/IPluginsManager.h"
#include "UI/IPluginExplorer.h"
#include "UI/ICommonControls.h"
#include "UI\IUIInterfaceManager.h"
#include <iostream>


using namespace UI;


void ListDLLFunctions(std::string sADllName, std::vector<std::string>& slListOfDllFunctions);


IPluginExplorer::IPluginExplorer()
{
}

IPluginExplorer::~IPluginExplorer()
{
}

void IPluginExplorer::LoadPlugin(const std::string &pluginName, std::vector<std::string> &functions)
{
	VT::IMessagePrinter *messagePrinter = VT::GetMessagePrinter();

	// Clear the output window
	messagePrinter->PrintMessage(VT::MsgCat_PluginExplorer, "", false, false);

	messagePrinter->PrintMessage(VT::MsgCat_PluginExplorer, 
		"Searching module for exported functions............... ", true, true);
	ListDLLFunctions(pluginName, functions);
	if (functions.empty())
		messagePrinter->PrintMessage(VT::MsgCat_PluginExplorer, 
			"No exported functions found.", true, true);
	else
		messagePrinter->PrintMessage(VT::MsgCat_PluginExplorer, 
			std::to_string(functions.size()) + " exported functions found.", true, true);
}

void IPluginExplorer::LoadPlugin()
{
	std::string pluginName = UI::GetCommonControls()->GetOpenFileName(
		GetControlImplementationSpecific(), "Open As", 
		Routines::GetBinDirectory(), ("dll Files (*.dll)"));

	std::vector<std::string> functions;
	LoadPlugin(pluginName, functions);
	AddPluginDataToTree(pluginName, functions);
}

void IPluginExplorer::ExecuteFunction(const std::string &pluginName, const std::string &functionName)
{
	VT::IMessagePrinter *messagePrinter = VT::GetMessagePrinter();

	// Clear the output window
	messagePrinter->PrintMessage(VT::MsgCat_PluginExplorer, "", false, false);

	auto msg{ "Attempting to run function \"" + functionName +
		"\" In plugin \"" + pluginName + "\"\n" };

	messagePrinter->PrintMessage(VT::MsgCat_PluginExplorer, msg, true, true);

	messagePrinter->PrintMessage(VT::MsgCat_PluginExplorer, "Result: ", true, true);

	VT::StdRedirector<> redirOut{ std::cout, VT::MsgCat_PluginExplorer };
	VT::StdRedirector<> redirErr{ std::cerr, VT::MsgCat_PluginExplorer };

	auto success{ true };

	try
	{
		VT::GetPluginsManager()->ExecuteFunction(pluginName, functionName);
	}
	catch (std::exception &e)
	{
		success = false;
		messagePrinter->PrintMessage(VT::MsgCat_PluginExplorer, e.what(), true, true);
	}
	catch (...)
	{
		success = false;
		messagePrinter->PrintMessage(VT::MsgCat_PluginExplorer, "Something went wrong.\n", true, true);
	}

	if (success)
		messagePrinter->PrintMessage(VT::MsgCat_PluginExplorer, "Call to function \"" + functionName + "\" ended successfully.\n", true, true);
}

void IPluginExplorer::AddPluginDataToTree(const std::string &pluginName,
	const std::vector<std::string> &functions)
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

void ListDLLFunctions(std::string sADllName, std::vector<std::string>& slListOfDllFunctions)
{
	unsigned long cDirSize;
	_LOADED_IMAGE LoadedImage;
	std::string sName;
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
