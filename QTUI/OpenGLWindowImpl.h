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

	void SetupThread();
	bool ReadyFrameToDraw();
	void DrawComplete(); 

private:
	std::unique_ptr <QOpenGLContext> context;

	// Destroying m_pParentObj is not our responsibility
	// QT mainwindow will handle it
	OpenGLWindow *parentObj;
};
