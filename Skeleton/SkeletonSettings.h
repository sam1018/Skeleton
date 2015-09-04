#pragma once

#include "Settings.h"
#include <string>

struct SkeletonSettings
{
	Settings::AttribAccessor accessor;
	bool hideCmdPromptAfterInitialization;
	int fps;
	std::string uiModule;
	std::string vitalsModule;

	SkeletonSettings(const std::string &fileName)
	{
		accessor.RegisterItem(hideCmdPromptAfterInitialization, "SkeletonSettings.HideCmdPromptAfterInitialization");
		accessor.RegisterItem(fps, "SkeletonSettings.FPS");
		accessor.RegisterItem(uiModule, "SkeletonSettings.UIModule");
		accessor.RegisterItem(vitalsModule, "SkeletonSettings.VitalsModule");

		accessor.Load(fileName);
	}
};
