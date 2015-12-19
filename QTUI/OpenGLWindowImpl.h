#pragma once

#include <memory>
#include <QtGui\QWindow>


///////////////////////////////////////////////////////
///     Implementation class for OpenGLWindow  ////////
///  So only OpenGLWindow is supposed to include it ///
///////////////////////////////////////////////////////

class OpenGLWindow;

class OpenGLWindowImpl : public QWindow
{
public:
	explicit OpenGLWindowImpl(OpenGLWindow* obj);
	~OpenGLWindowImpl();

	void exposeEvent(QExposeEvent *) Q_DECL_OVERRIDE;

	void SetupThread();
	bool ReadyFrameToDraw();
	void DrawComplete();

private:
	void SetupOpenGL();

private:
	std::unique_ptr <QOpenGLContext> context;

	// non-owning
	OpenGLWindow *parentObj;

	bool contextInSeparateThread;
};
