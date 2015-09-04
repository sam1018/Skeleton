#pragma once

#include "UIItem.h"
#include "SkeletonInterface.h"

namespace OGLWnd
{
	void CallbackSetupThread();
	bool CallbackStartCycle();
	void CallbackEndCycle();

	class SKELETONINTERFACE_DECLSPEC IOpenGLWindow : public UI::UIItem
	{
	public:
		IOpenGLWindow();
		virtual ~IOpenGLWindow();

		void InitializeItem();
		void Cleanup();

		// Following functions will be called from the thread responsible for drawing
		virtual void SetupThread() = 0;
		virtual bool ReadyFrameToDraw() = 0;
		virtual void DrawComplete() = 0;
	};
}
