#pragma once

#include "../SkeletonInterface/IOpenGLWindow.h"

class QWindow;
class OpenGLWindowImpl;

class OpenGLWindow : public OGLWnd::IOpenGLWindow
{
public:
	OpenGLWindow();
	~OpenGLWindow();

	// Use GetOpenGLWindowImpl() to get object with proper type
	void* GetImpl();
	QWindow* GetOpenGLWindowImpl();

	void Update();

private:
	// MainWindowImpl is responsible for destroying it
	OpenGLWindowImpl* openGLWindowImpl;
};
