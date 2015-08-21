#pragma once

#include "../SkeletonInterface/Settings.h"
#include <string>

struct QTGUISettings
{
	Settings::AttribAccessor Accessor;
	int m_MonitorIndex;

	QTGUISettings()
	{
		Accessor.RegisterItem(m_MonitorIndex, "QTGUISettings.MonitorIndex");
	}

	void Load(std::string fileName)
	{
		Accessor.Load(fileName);
	}

	void Save(std::string fileName)
	{
		Accessor.Save(fileName);
	}

	static QTGUISettings& GetInstance()
	{
		static QTGUISettings settings;
		return settings;
	}
};
