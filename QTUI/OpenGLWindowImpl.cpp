#include "OpenGLWindow.h"
#include "OpenGLWindowImpl.h"
#include <QtCore\QThread>
#include <QtGui\QOpenGLContext>

using namespace std;


///////////////////////////////////////////////////////////////////////////////
/////////////          OpenGLWindowImpl Definition                 ////////////
///////////////////////////////////////////////////////////////////////////////


OpenGLWindowImpl::OpenGLWindowImpl(OpenGLWindow* obj) :
	parentObj{ obj },
	contextInSeparateThread{ false }
{
	SetupOpenGL();
}

OpenGLWindowImpl::~OpenGLWindowImpl()
{
}

void OpenGLWindowImpl::SetupOpenGL()
{
	setSurfaceType(QWindow::OpenGLSurface);

	delete context.release();

	context = make_unique<QOpenGLContext>();
	context->create();

	context->doneCurrent();
	context->moveToThread(QThread::currentThread());
}

void OpenGLWindowImpl::SetupThread()
{
	SetupOpenGL();
	contextInSeparateThread = true;
}

bool OpenGLWindowImpl::ReadyFrameToDraw()
{
	if (isExposed())
	{
		context->makeCurrent(this);
		glViewport(0, 0, this->width() * this->devicePixelRatio(), this->height() * this->devicePixelRatio());
		return true;
	}

	return false;
}

void OpenGLWindowImpl::DrawComplete()
{
	if(isExposed())
		context->swapBuffers(this);
}

void OpenGLWindowImpl::exposeEvent(QExposeEvent *)
{
	if (isExposed() && !contextInSeparateThread)
	{
		ReadyFrameToDraw();
		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT);
		DrawComplete();
	}
}
