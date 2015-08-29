#include "IOpenGLWindow.h"
#include "FunctionManager.h"
#include "ICoreGUIApplication.h"

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
	using namespace FctEx;

	FunctionManager::GetInstance().CallbackSetupThread(OGLWnd::CallbackSetupThread);
	FunctionManager::GetInstance().CallbackStartCycle(OGLWnd::CallbackStartCycle);
	FunctionManager::GetInstance().CallbackEndCycle(OGLWnd::CallbackEndCycle);

	FunctionManager::GetInstance().StartThread();
}

void ICoreGUIApplication::FPSHandler()
{
	using namespace FctEx;

	if (FunctionManager::GetInstance().ReadyForNewCycle())
	{
		//OGLWnd::Update();
		FunctionManager::GetInstance().RequestNewCycle();
	}
}
