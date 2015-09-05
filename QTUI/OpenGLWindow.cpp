#include "OpenGLWindow.h"
#include "OpenGLWindowImpl.h"


///////////////////////////////////////////////////////////////////////////////
/////////////          OpenGLWindow Definition                     ////////////
///////////////////////////////////////////////////////////////////////////////


OpenGLWindow::OpenGLWindow() :
	openGLWindowImpl{ new OpenGLWindowImpl{this} }
{
}


OpenGLWindow::~OpenGLWindow()
{
}

void OpenGLWindow::SetupThread_()
{
	openGLWindowImpl->SetupThread();
}

bool OpenGLWindow::ReadyFrameToDraw_()
{
	return openGLWindowImpl->ReadyFrameToDraw();
}

void OpenGLWindow::DrawComplete_()
{
	openGLWindowImpl->DrawComplete();
}

QWindow* OpenGLWindow::GetOpenGLWindowImpl()
{
	return openGLWindowImpl;
}
