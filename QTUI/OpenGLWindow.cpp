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
	//glViewport(0, 0, m_pImpl->width() * m_pImpl->devicePixelRatio(), m_pImpl->height() * m_pImpl->devicePixelRatio());
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glClearColor(.5, .5, .5, .5);
	//glFrontFace(GL_CW);
	//glCullFace(GL_FRONT);
	//glEnable(GL_CULL_FACE);
	//glEnable(GL_DEPTH_TEST);

	TestUpdate();
}
