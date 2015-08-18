#pragma once

#include <memory>
#include <QtCore\QTimer>
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
	std::unique_ptr <QOpenGLContext> m_pContext;
	std::unique_ptr <QTimer> m_pTimer;

	// Destroying m_pParentObj is not our responsibility
	OpenGLWindow *m_pParentObj;
};
