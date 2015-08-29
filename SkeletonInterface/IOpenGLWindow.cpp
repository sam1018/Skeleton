#include "IOpenGLWindow.h"

using namespace OGLWnd;


IOpenGLWindow *openGLWindow;


void OGLWnd::CallbackSetupThread()
{
	openGLWindow->SetupThread();
}

bool OGLWnd::CallbackStartCycle()
{
	return openGLWindow->ReadyFrameToDraw();
}

void OGLWnd::CallbackEndCycle()
{
	openGLWindow->DrawComplete();
}



///////////////////////////////////////////////////////////////////////////////
/////////////          IOpenGLWindow Definition                    ////////////
///////////////////////////////////////////////////////////////////////////////

IOpenGLWindow::IOpenGLWindow()
{
}


IOpenGLWindow::~IOpenGLWindow()
{
}

void IOpenGLWindow::InitializeItem()
{
	openGLWindow = this;
}

void IOpenGLWindow::Cleanup()
{
	openGLWindow = nullptr;
}
