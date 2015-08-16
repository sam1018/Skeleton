#pragma once

#include "IPlugin.h"

class IMainWindow;
class IOpenGLWindow;

class PluginUI : public IPlugin
{
public:
	PluginUI();
	~PluginUI();

	IMainWindow* GetMainWindow();
	IOpenGLWindow* GetOpenGLWindow();

	int Run();
};
