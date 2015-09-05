#pragma once

#include "SkeletonInterface.h"

namespace UI
{
	class SKELETONINTERFACE_DECLSPEC IOpenGLWindow
	{
	public:
		IOpenGLWindow();
		virtual ~IOpenGLWindow();

		// Following functions will be called from the thread responsible for drawing
		void CallbackSetupThread();
		bool CallbackStartCycle();
		void CallbackEndCycle();

	private:
		virtual void SetupThread_() = 0;
		virtual bool ReadyFrameToDraw_() = 0;
		virtual void DrawComplete_() = 0;
	};
}
