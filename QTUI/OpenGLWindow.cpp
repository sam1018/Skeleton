#include "OpenGLWindow.h"
#include "OpenGLWindowImpl.h"

OpenGLWindow::OpenGLWindow() :
	m_pImpl{ new OpenGLWindowImpl{this} }
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
	return m_pImpl;
}
