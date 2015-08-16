#pragma once

#include "../SkeletonInterface/IOpenGLWindow.h"

class OpenGLWindowImpl;

class OpenGLWindow : public IOpenGLWindow
{
public:
	OpenGLWindow();
	~OpenGLWindow();

	OpenGLWindowImpl* GetOpenGLWindowImpl() { return m_pImpl; }

	void Update();

private:
	OpenGLWindowImpl* m_pImpl;
};
