#pragma once

#include "../SkeletonInterface/Settings.h"
#include <string>

struct SkeletonSettings
{
	Settings::AttribAccessor Accessor;
	std::string m_UIPluginName;
	bool m_bHideCmdPromptAfterInitialization;

	SkeletonSettings()
	{
		Accessor.RegisterItem(m_UIPluginName, "SkeletonSettings.PluginsList.UIPlugin");
		Accessor.RegisterItem(m_bHideCmdPromptAfterInitialization, "SkeletonSettings.HideCmdPromptAfterInitialization");
	}

	void Load(std::string fileName)
	{
		Accessor.Load(fileName);
	}

	static SkeletonSettings& GetInstance()
	{
		static SkeletonSettings settings;
		return settings;
	}
};
