#pragma once

#include "../SkeletonInterface/Settings.h"
#include <string>

struct SkeletonSettings
{
	Settings::AttribAccessor accessor;
	bool hideCmdPromptAfterInitialization;

	void Load(std::string fileName)
	{
		accessor.Load(fileName);
	}

	static SkeletonSettings& GetInstance()
	{
		static SkeletonSettings settings;
		return settings;
	}

private:
	SkeletonSettings()
	{
		accessor.RegisterItem(hideCmdPromptAfterInitialization, "SkeletonSettings.HideCmdPromptAfterInitialization");
	}
};
