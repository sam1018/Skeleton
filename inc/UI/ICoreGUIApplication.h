#pragma once

#include "UIItem.h"
#include "SkeletonInterface.h"
#include <functional>

namespace CGA
{
	SKELETONINTERFACE_DECLSPEC int Run();

	SKELETONINTERFACE_DECLSPEC void SetupFPS(int fps);

	SKELETONINTERFACE_DECLSPEC void FinishInitialization();

	class SKELETONINTERFACE_DECLSPEC ICoreGUIApplication : public UI::UIItem
	{
	public:
		ICoreGUIApplication();
		virtual ~ICoreGUIApplication() = 0;

		void InitializeItem();
		void Cleanup();

		void FinishInitialization();

		virtual int Run() = 0;

		virtual void SetupFPS(int fps) = 0;

		void FPSHandler();
	};
}
