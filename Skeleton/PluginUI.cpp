#include "PluginUI.h"
#include "../SkeletonInterface/IMainWindow.h"
#include <functional>

PluginUI::PluginUI()
{
}

PluginUI::~PluginUI()
{
}

IMainWindow* PluginUI::GetMainWindow()
{
	return PluginCallerBody<IMainWindow*>(__func__);
}

int PluginUI::Run()
{
	return PluginCallerBody<int>(__func__);
}
