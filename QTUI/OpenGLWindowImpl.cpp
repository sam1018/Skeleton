#include "OpenGLWindowImpl.h"
#include "OpenGLWindow.h"
#include <QtCore\QTimer>
#include <QtGui\QOpenGLContext>


///////////////////////////////////////////////////////////////////////////////
/////////////          OpenGLWindowImpl Definition                 ////////////
///////////////////////////////////////////////////////////////////////////////


OpenGLWindowImpl::OpenGLWindowImpl(OpenGLWindow* obj) :
	timer{ std::make_unique<QTimer>(this) },
	context{ std::make_unique<QOpenGLContext>() },
	parentObj{ obj }
{
	connect(timer.get(), SIGNAL(timeout()), this, SLOT(Update()));
	timer->start(1000);

	setSurfaceType(QWindow::OpenGLSurface);
	context->create();
}

OpenGLWindowImpl::~OpenGLWindowImpl()
{
}

void OpenGLWindowImpl::Update()
{
	if (isExposed())
	{
		context->makeCurrent(this);

		glViewport(0, 0, this->width() * this->devicePixelRatio(), this->height() * this->devicePixelRatio());

		parentObj->Update();

		context->swapBuffers(this);
	}
}
