#include "OpenGLWindowImpl.h"
#include <QtGui\QOpenGLContext>
#include "OpenGLWindow.h"

OpenGLWindowImpl::OpenGLWindowImpl(OpenGLWindow* obj) :
	m_pContext{ std::make_unique<QOpenGLContext>() },
	m_pTimer{ std::make_unique<QTimer>() },
	m_pParentObj{ obj }
{
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(Update()));
	timer->start(1000);

	setSurfaceType(QWindow::OpenGLSurface);
	m_pContext->create();
}

OpenGLWindowImpl::~OpenGLWindowImpl()
{
}

void OpenGLWindowImpl::Update()
{
	if (isExposed())
	{
		m_pContext->makeCurrent(this);

		glViewport(0, 0, this->width() * this->devicePixelRatio(), this->height() * this->devicePixelRatio());

		m_pParentObj->Update();

		m_pContext->swapBuffers(this);
	}
}