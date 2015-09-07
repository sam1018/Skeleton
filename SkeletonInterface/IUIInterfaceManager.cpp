#include "UI\IUIInterfaceManager.h"
#include <cassert>


using namespace UI;


#define ADD_PROP(RetType, FuncName) \
RetType FuncName() \
{ \
	assert(uiInterfaceManager != nullptr); \
	return uiInterfaceManager->FuncName(); \
}

namespace UI
{
	class UIInterfaceMngrAccessor
	{
	public:
		void SetUIInterfaceManager(IUIInterfaceManager *val)
		{
			uiInterfaceManager = val;
		}

		ADD_PROP(ICommonControls*, GetCommonControls)
		ADD_PROP(ICoreGUIApplication*, GetCoreGUIApplication)
		ADD_PROP(IMainWindow*, GetMainWindow)
		ADD_PROP(IOpenGLWindow*, GetOpenGLWindow)
		ADD_PROP(IOutputWindow*, GetOutputWindow)

	private:
		IUIInterfaceManager *uiInterfaceManager = nullptr;

	} uiInterfaceMngrAccessor;
}

IUIInterfaceManager::~IUIInterfaceManager()
{
}

void UI::SetUIInterfaceManager(IUIInterfaceManager *uiInterfaceManager)
{
	uiInterfaceMngrAccessor.SetUIInterfaceManager(uiInterfaceManager);
}

ICommonControls* UI::GetCommonControls()
{
	return uiInterfaceMngrAccessor.GetCommonControls();
}

ICoreGUIApplication* UI::GetCoreGUIApplication()
{
	return uiInterfaceMngrAccessor.GetCoreGUIApplication();
}

IMainWindow* UI::GetMainWindow()
{
	return uiInterfaceMngrAccessor.GetMainWindow();
}

IOpenGLWindow* UI::GetOpenGLWindow()
{
	return uiInterfaceMngrAccessor.GetOpenGLWindow();
}

IOutputWindow * UI::GetOutputWindow()
{
	return uiInterfaceMngrAccessor.GetOutputWindow();
}
