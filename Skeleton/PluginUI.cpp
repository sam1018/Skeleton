#include "PluginUI.h"
#include "../SkeletonInterface/IMainWindow.h"

typedef IMainWindow* (__cdecl *GetMainWindowFunc)(void);

PluginUI::PluginUI()
{
}

PluginUI::~PluginUI()
{
}

IMainWindow* PluginUI::GetMainWindow()
{
	GetMainWindowFunc GetMainWindow = (GetMainWindowFunc) GetFunctionAddress("GetMainWindow");
	return GetMainWindow();
}
