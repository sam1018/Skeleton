#pragma once

#include <QtGui\QWindow>

class OpenGLWindow;

class OpenGLWindowImpl : public QWindow
{
	Q_OBJECT

public:
	OpenGLWindowImpl(OpenGLWindow* obj);
	~OpenGLWindowImpl();

private slots:
	void Update();

private:
	QOpenGLContext *m_pContext;
	OpenGLWindow *m_pParentObj;
};
