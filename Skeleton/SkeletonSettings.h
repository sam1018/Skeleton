#pragma once

#include "../SkeletonInterface/Settings.h"
#include <string>

struct SkeletonSettings
{
	Settings::AttribAccessor accessor;
	bool hideCmdPromptAfterInitialization;
	int fps;

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
		accessor.RegisterItem(fps, "SkeletonSettings.FPS");
	}
};
