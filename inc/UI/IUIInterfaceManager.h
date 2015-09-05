#pragma once

#include "../SkeletonInterface.h"

namespace UI
{
	class ICommonControls;
	class ICoreGUIApplication;
	class IMainWindow;
	class IOpenGLWindow;

	class SKELETONINTERFACE_DECLSPEC IUIInterfaceManager
	{
		friend class UIInterfaceMngrAccessor;

	public:
		virtual ~IUIInterfaceManager() = 0;

	private:
		virtual ICommonControls* GetCommonControls() = 0;
		virtual ICoreGUIApplication* GetCoreGUIApplication() = 0;
		virtual IMainWindow* GetMainWindow() = 0;
		virtual IOpenGLWindow* GetOpenGLWindow() = 0;
	};

	SKELETONINTERFACE_DECLSPEC void SetUIInterfaceManager(IUIInterfaceManager*);

	SKELETONINTERFACE_DECLSPEC ICommonControls* GetCommonControls();
	SKELETONINTERFACE_DECLSPEC ICoreGUIApplication* GetCoreGUIApplication();
	SKELETONINTERFACE_DECLSPEC IMainWindow* GetMainWindow();
	SKELETONINTERFACE_DECLSPEC IOpenGLWindow* GetOpenGLWindow();
}
