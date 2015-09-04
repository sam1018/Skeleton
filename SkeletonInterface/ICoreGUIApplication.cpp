#include "UI\IOpenGLWindow.h"
#include "Vitals\ICallerManager.h"
#include "Vitals\IVitalsInterfaceManager.h"
#include "UI\ICoreGUIApplication.h"

using namespace CGA;

ICoreGUIApplication *coreGUIApplication;


void ThrowUninitializedClass(std::string className)
{
	throw std::exception((className + " class is not initialized").c_str());
}


int CGA::Run()
{
	if (!coreGUIApplication)
		ThrowUninitializedClass("ICoreGUIApplication");

	return coreGUIApplication->Run();
}

void CGA::SetupFPS(int fps)
{
	coreGUIApplication->SetupFPS(fps);
}

void CGA::FinishInitialization()
{
	coreGUIApplication->FinishInitialization();
}


///////////////////////////////////////////////////////////////////////////////
/////////////          ICoreGUIApplication Definition              ////////////
///////////////////////////////////////////////////////////////////////////////


ICoreGUIApplication::ICoreGUIApplication()
{
}

ICoreGUIApplication::~ICoreGUIApplication()
{
}

void ICoreGUIApplication::InitializeItem()
{
	coreGUIApplication = this;
}

void ICoreGUIApplication::Cleanup()
{
	coreGUIApplication = nullptr;
}

void ICoreGUIApplication::FinishInitialization()
{
	using namespace VT;
	ICallerManager *fctMngr = GetCallerManager();

	fctMngr->CallbackSetupThread(OGLWnd::CallbackSetupThread);
	fctMngr->CallbackStartCycle(OGLWnd::CallbackStartCycle);
	fctMngr->CallbackEndCycle(OGLWnd::CallbackEndCycle);

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
