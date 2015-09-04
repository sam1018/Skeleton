#include "Routines.h"
#include "UI/IOutputWindow.h"
#include "Vitals\IVitalsInterfaceManager.h"
#include "Vitals/IPluginsManager.h"
#include "UI/IPluginExplorer.h"
#include "UI/CommonControls.h"
#include <iostream>



using namespace PE;


void ListDLLFunctions(std::string sADllName, std::vector<std::string>& slListOfDllFunctions);


struct IPluginExplorer::IPluginExplorerImpl
{
	OutWnd::OutWndCatID outWndID;

	IPluginExplorerImpl() :
		outWndID{ OutWnd::RegisterOutputWindowCategory(OutWnd::OutWndPluginExplorerCategory) }
	{}
};


IPluginExplorer::IPluginExplorer() :
	pluginExplorerImpl{ std::make_unique<IPluginExplorer::IPluginExplorerImpl>() }
{
}

IPluginExplorer::~IPluginExplorer()
{
}

void IPluginExplorer::InitializeItem()
{
}

void IPluginExplorer::Cleanup()
{
}

void IPluginExplorer::LoadPlugin(const std::string &pluginName, std::vector<std::string> &functions)
{
	// Clear the output window
	OutWnd::OutputWindowSetText(pluginExplorerImpl->outWndID, "", false, false);

	OutWnd::OutputWindowSetText(pluginExplorerImpl->outWndID, "Searching module for exported functions............... ", true, true);
	ListDLLFunctions(pluginName, functions);
	if (functions.empty())
		OutWnd::OutputWindowSetText(pluginExplorerImpl->outWndID, "No exported functions found.", true, true);
	else
		OutWnd::OutputWindowSetText(pluginExplorerImpl->outWndID, std::to_string(functions.size()) + " exported functions found.", true, true);
}

void IPluginExplorer::LoadPlugin()
{
	std::string pluginName = CommCtrls::FileDialog::GetOpenFileName(this, "Open As", Routines::GetBinDirectory(), ("dll Files (*.dll)"));
	std::vector<std::string> functions;
	LoadPlugin(pluginName, functions);
	AddPluginDataToTree(pluginName, functions);
}

void IPluginExplorer::ExecuteFunction(const std::string &pluginName, const std::string &functionName)
{
	// Clear the output window
	OutWnd::OutputWindowSetText(pluginExplorerImpl->outWndID, "", false, false);

	auto msg{ "Attempting to run function \"" + functionName +
		"\" In plugin \"" + pluginName + "\"\n" };

	OutWnd::OutputWindowSetText(pluginExplorerImpl->outWndID, msg, true, true);

	OutWnd::OutputWindowSetText(pluginExplorerImpl->outWndID, "Result: ", true, true);

	OutWnd::StdRedirector<> redirOut{ std::cout, pluginExplorerImpl->outWndID };
	OutWnd::StdRedirector<> redirErr{ std::cerr, pluginExplorerImpl->outWndID };

	auto success{ true };

	try
	{
		VT::GetPluginsManager()->ExecuteFunctionDynamic(pluginName, functionName);
	}
	catch (std::exception &e)
	{
		success = false;
		OutWnd::OutputWindowSetText(pluginExplorerImpl->outWndID, e.what(), true, true);
	}
	catch (...)
	{
		success = false;
		OutWnd::OutputWindowSetText(pluginExplorerImpl->outWndID, "Something went wrong.\n", true, true);
	}

	if (success)
		OutWnd::OutputWindowSetText(pluginExplorerImpl->outWndID, "Call to function \"" + functionName + "\" ended successfully.\n", true, true);
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
