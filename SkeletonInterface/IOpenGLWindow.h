#pragma once

#include "UIItem.h"
#include "SkeletonInterface.h"
#include <windows.h>
#include <gl\GL.h>

namespace OGLWnd
{
	class SKELETONINTERFACE_DECLSPEC IOpenGLWindow : public UI::UIItem
	{
	public:
		IOpenGLWindow();
		virtual ~IOpenGLWindow();

		void InitializeItem();
		void Cleanup();

	protected:
		void TestUpdate()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glClearColor(1, 0, 0, 1);
			glFrontFace(GL_CW);
			glCullFace(GL_FRONT);
			glEnable(GL_CULL_FACE);
			glEnable(GL_DEPTH_TEST);
		}
	};
}
