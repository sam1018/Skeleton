#include "IPluginExplorer.h"
#include "IOutputWindow.h"
#include "PluginsManager.h"
#include <Windows.h>

// I hate warnings
#pragma warning( push )
#pragma warning( disable : 4091 )
#include <Imagehlp.h>
#pragma warning( pop )

using namespace PE;

struct IPluginExplorer::IPluginExplorerImpl
{
	OutWnd::OutWndCatID outWndID;

	IPluginExplorerImpl() :
		outWndID{ OutWnd::RegisterOutputWindowCategory(OutWnd::OutWndPluginExplorerCategory) }
	{}
};

void ListDLLFunctions(std::string sADllName, std::vector<std::string>& slListOfDllFunctions)
{
	DWORD *dNameRVAs(0);
	_IMAGE_EXPORT_DIRECTORY *ImageExportDirectory;
	unsigned long cDirSize;
	_LOADED_IMAGE LoadedImage;
	std::string sName;
	slListOfDllFunctions.clear();
	if (MapAndLoad(sADllName.c_str(), NULL, &LoadedImage, TRUE, TRUE))
	{
		ImageExportDirectory = (_IMAGE_EXPORT_DIRECTORY*)
			ImageDirectoryEntryToData(LoadedImage.MappedAddress,
				false, IMAGE_DIRECTORY_ENTRY_EXPORT, &cDirSize);
		if (ImageExportDirectory != NULL)
		{
			dNameRVAs = (DWORD *)ImageRvaToVa(LoadedImage.FileHeader,
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

void IPluginExplorer::LoadPlugin(std::string pluginName, std::vector<std::string>& functions)
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

void IPluginExplorer::ExecuteFunction(std::string pluginName, std::string functionName)
{
	PluginsManager::GetInstance().ExecuteFunctionDynamic(pluginName, functionName);
}
