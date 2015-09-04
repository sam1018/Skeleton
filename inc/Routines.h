#pragma once

#include "SkeletonInterface.h"
#include <string>

namespace Routines
{
	// Sets the full binary file path with name
	// main function is responsible to set this by using argv[0]
	void SKELETONINTERFACE_DECLSPEC SetBinFilePath(std::string path);

	std::string SKELETONINTERFACE_DECLSPEC GetBinDirectory();

	// Returns $(HOME_DIR)/Skeleton/, creates the folder if not present
	// throws error if cannot be created
	// https://en.wikipedia.org/wiki/Home_directory
	std::string SKELETONINTERFACE_DECLSPEC GetUserDir();

	// Returns $(GetUserDir())/Settings/
	// Creates if already not present
	// throws error if cannot be created
	std::string SKELETONINTERFACE_DECLSPEC GetUserSettingsDir();

	// Returns $(BinFilePath)/Settings
	// Creates if already not present
	// throws error if cannot be created
	std::string SKELETONINTERFACE_DECLSPEC GetFactorySettingsDir();

	// Returns $(GetUserSettingsDir())/filename
	// Doesn't check for existance
	std::string SKELETONINTERFACE_DECLSPEC GetSettingsFileFullPath_Save(std::string fileName);

	// Absolute file path for the settings file is returned
	// Following logic is applied to create the file path
	// If $(GetUserSettingsDir())/filename exists, this name is returned
	// else if $(GetFactorySettingsDir())/filename exist, this name is returned
	// else throws error
	std::string SKELETONINTERFACE_DECLSPEC GetSettingsFileFullPath_Load(std::string fileName);

	// Returns the binary executable name
	std::string SKELETONINTERFACE_DECLSPEC GetApplicationName();

	// Returns company name
	std::string SKELETONINTERFACE_DECLSPEC GetCompanyName();

	std::string SKELETONINTERFACE_DECLSPEC GetFileNameFromPath(std::string path);

	bool SKELETONINTERFACE_DECLSPEC IsSamePath(std::string path1, std::string path2);
}
