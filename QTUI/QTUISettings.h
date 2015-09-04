#pragma once

#include "QTUI.h"
#include "Settings.h"
#include <string>

struct QTUISettings
{
	Settings::AttribAccessor accessor;

	QTUISettings()
	{
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
