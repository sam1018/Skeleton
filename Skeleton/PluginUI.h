#pragma once

#include "IPlugin.h"

class IMainWindow;

class PluginUI : public IPlugin
{
public:
	PluginUI();
	~PluginUI();

	IMainWindow* GetMainWindow();
};
