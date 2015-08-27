#pragma once

#include "UIItem.h"
#include "SkeletonInterface.h"

namespace OGLWnd
{
	class SKELETONINTERFACE_DECLSPEC IOpenGLWindow : public UI::UIItem
	{
	public:
		IOpenGLWindow();
		virtual ~IOpenGLWindow();

		void InitializeItem();
		void Cleanup();
	};
}
