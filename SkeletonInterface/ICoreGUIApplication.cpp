#include "UI\IOpenGLWindow.h"
#include "Vitals\ICallerManager.h"
#include "Vitals\IVitalsInterfaceManager.h"
#include "UI\ICoreGUIApplication.h"
#include "UI\IUIInterfaceManager.h"

using namespace UI;
using namespace VT;


///////////////////////////////////////////////////////////////////////////////
/////////////          ICoreGUIApplication Definition              ////////////
///////////////////////////////////////////////////////////////////////////////


ICoreGUIApplication::ICoreGUIApplication()
{
}

ICoreGUIApplication::~ICoreGUIApplication()
{
}

void ICoreGUIApplication::FinishInitialization()
{
	ICallerManager *fctMngr = GetCallerManager();
	IOpenGLWindow *oglWnd = GetOpenGLWindow();


	fctMngr->CallbackSetupThread([oglWnd]() { oglWnd->CallbackSetupThread(); });
	fctMngr->CallbackStartCycle([oglWnd]() { return oglWnd->CallbackStartCycle(); });
	fctMngr->CallbackEndCycle([oglWnd]() { oglWnd->CallbackEndCycle(); });

	fctMngr->StartThread();
}

void ICoreGUIApplication::FPSHandler()
{
	using namespace VT;
	ICallerManager *fctMngr = GetCallerManager();

	if (fctMngr->ReadyForNewCycle())
	{
		//OGLWnd::Update();
		fctMngr->RequestNewCycle();
	}
}

int ICoreGUIApplication::Run()
{
	return Run_();
}

void ICoreGUIApplication::SetupFPS(int fps)
{
	return SetupFPS_(fps);
}
