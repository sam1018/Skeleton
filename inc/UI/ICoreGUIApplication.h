#pragma once

#include "SkeletonInterface.h"
#include <functional>

namespace UI
{
	class SKELETONINTERFACE_DECLSPEC ICoreGUIApplication
	{
	public:
		ICoreGUIApplication();
		virtual ~ICoreGUIApplication() = 0;

		void FinishInitialization();

		//void FPSHandler();

		int Run();

		void SetupFPS(int fps);

	private:
		virtual int Run_() = 0;
		//virtual void SetupFPS_(int fps) = 0;
	};
}
