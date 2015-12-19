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
	ICallerManager *callerMngr = GetCallerManager();
	IOpenGLWindow *oglWnd = GetOpenGLWindow();


	callerMngr->CallbackSetupThread([oglWnd]() { oglWnd->CallbackSetupThread(); });
	callerMngr->CallbackStartCycle([oglWnd]() { return oglWnd->CallbackStartCycle(); });
	callerMngr->CallbackEndCycle([oglWnd]() { oglWnd->CallbackEndCycle(); });
}

int ICoreGUIApplication::Run()
{
	return Run_();
}
