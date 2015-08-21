#pragma once

#include "../SkeletonInterface/Settings.h"
#include <string>

struct SkeletonSettings
{
	Settings::AttribAccessor accessor;
	std::string uiPluginName;
	bool hideCmdPromptAfterInitialization;

	SkeletonSettings()
	{
		accessor.RegisterItem(uiPluginName, "SkeletonSettings.PluginsList.UIPlugin");
		accessor.RegisterItem(hideCmdPromptAfterInitialization, "SkeletonSettings.HideCmdPromptAfterInitialization");
	}

	void Load(std::string fileName)
	{
		accessor.Load(fileName);
	}

	static SkeletonSettings& GetInstance()
	{
		static SkeletonSettings settings;
		return settings;
	}
};
