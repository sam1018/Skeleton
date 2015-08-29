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

void* OpenGLWindow::GetImpl()
{
	return openGLWindowImpl;
}

void OpenGLWindow::SetupThread()
{
	openGLWindowImpl->SetupThread();
}

bool OpenGLWindow::ReadyFrameToDraw()
{
	return openGLWindowImpl->ReadyFrameToDraw();
}

void OpenGLWindow::DrawComplete()
{
	openGLWindowImpl->DrawComplete();
}

QWindow* OpenGLWindow::GetOpenGLWindowImpl()
{
	return openGLWindowImpl;
}
