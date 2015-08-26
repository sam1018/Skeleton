#pragma once

#include "Settings.h"
#include <string>

struct StaticPlugins
{
	Settings::AttribAccessor accessor;
	std::string uiPluginName;

	void Load(std::string fileName)
	{
		accessor.Load(fileName);
	}

	static StaticPlugins& GetInstance()
	{
		static StaticPlugins settings;
		return settings;
	}

private:
	StaticPlugins()
	{
		accessor.RegisterItem(uiPluginName, "StaticPluginsList.UIPlugin");
	}
};
