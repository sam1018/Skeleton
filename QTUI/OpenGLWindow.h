#pragma once

#include "UI/IOpenGLWindow.h"

class QWindow;
class OpenGLWindowImpl;

class OpenGLWindow : public UI::IOpenGLWindow
{
public:
	OpenGLWindow();
	~OpenGLWindow();

	QWindow* GetOpenGLWindowImpl();

private:
	virtual void SetupThread_();
	virtual bool ReadyFrameToDraw_();
	virtual void DrawComplete_();

private:
	// MainWindowImpl is responsible for destroying it
	OpenGLWindowImpl* openGLWindowImpl;
};
