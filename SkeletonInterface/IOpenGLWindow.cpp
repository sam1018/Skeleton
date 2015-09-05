#include "UI\IOpenGLWindow.h"

using namespace UI;


///////////////////////////////////////////////////////////////////////////////
/////////////          IOpenGLWindow Definition                    ////////////
///////////////////////////////////////////////////////////////////////////////

IOpenGLWindow::IOpenGLWindow()
{
}


IOpenGLWindow::~IOpenGLWindow()
{
}

void IOpenGLWindow::CallbackSetupThread()
{
	SetupThread_();
}

bool IOpenGLWindow::CallbackStartCycle()
{
	return ReadyFrameToDraw_();
}

void IOpenGLWindow::CallbackEndCycle()
{
	DrawComplete_();
}
