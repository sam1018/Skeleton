#include "OpenGLWindow.h"
#include "OpenGLWindowImpl.h"
#include <QtCore\QThread>
#include <QtGui\QOpenGLContext>

using namespace std;


///////////////////////////////////////////////////////////////////////////////
/////////////          OpenGLWindowImpl Definition                 ////////////
///////////////////////////////////////////////////////////////////////////////


OpenGLWindowImpl::OpenGLWindowImpl(OpenGLWindow* obj) :
	parentObj{ obj }
{
	setSurfaceType(QWindow::OpenGLSurface);
}

OpenGLWindowImpl::~OpenGLWindowImpl()
{
}

void OpenGLWindowImpl::SetupThread()
{
	context = make_unique<QOpenGLContext>();
	context->create();

	context->doneCurrent();
	context->moveToThread(QThread::currentThread());
	
	glViewport(0, 0, this->width() * this->devicePixelRatio(), this->height() * this->devicePixelRatio());
}

bool OpenGLWindowImpl::ReadyFrameToDraw()
{
	if (isExposed())
	{
		context->makeCurrent(this);
		return true;
	}

	return false;
}

void OpenGLWindowImpl::DrawComplete()
{
	if(isExposed())
		context->swapBuffers(this);
}
