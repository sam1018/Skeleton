#pragma once

#include "QTUI.h"
#include "../SkeletonInterface/Settings.h"
#include <string>

struct QTUISettings
{
	Settings::AttribAccessor accessor;
	int monitorIndex;

	QTUISettings()
	{
		accessor.RegisterItem(monitorIndex, "QTUISettings.MonitorIndex");
	}

	void Load(std::string fileName)
	{
		accessor.Load(fileName);
	}

	void Save(std::string fileName)
	{
		accessor.Save(fileName);
	}
};


// Call this function to get settings attributes
QTUISettings& GetQTUISettings();
