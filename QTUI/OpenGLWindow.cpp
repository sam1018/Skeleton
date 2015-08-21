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

void OpenGLWindow::Update()
{
	TestUpdate();
}

QWindow* OpenGLWindow::GetOpenGLWindowImpl()
{
	return openGLWindowImpl;
}
