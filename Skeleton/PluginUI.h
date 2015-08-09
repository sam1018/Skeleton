#pragma once

#include "IPlugin.h"

class IMainFrame;

class PluginUI : public IPlugin
{
public:
	PluginUI();
	~PluginUI();

	std::unique_ptr <IMainFrame> CreateMainFrame();
};
