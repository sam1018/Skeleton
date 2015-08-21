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
	Q_OBJECT

public:
	OpenGLWindowImpl(OpenGLWindow* obj);
	~OpenGLWindowImpl();

	private slots:
	void Update();

private:
	std::unique_ptr <QTimer> timer;
	std::unique_ptr <QOpenGLContext> context;

	// Destroying m_pParentObj is not our responsibility
	// QT mainwindow will handle it
	OpenGLWindow *parentObj;
};
