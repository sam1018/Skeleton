#include "PluginUI.h"
#include "IMainFrame.h"

typedef std::unique_ptr <IMainFrame>(__cdecl *CreateMainFrameFunc)(void);

PluginUI::PluginUI()
{
}

PluginUI::~PluginUI()
{
}

std::unique_ptr <IMainFrame> PluginUI::CreateMainFrame()
{
	CreateMainFrameFunc CreateMainFrame = (CreateMainFrameFunc) GetFunctionAddress("CreateMainFrame");
	return CreateMainFrame();
}
