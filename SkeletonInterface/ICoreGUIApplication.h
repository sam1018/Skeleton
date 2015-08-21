#pragma once

#include "SkeletonInterface.h"

namespace GUI
{
	SKELETONINTERFACE_DECLSPEC int Run();

	class SKELETONINTERFACE_DECLSPEC ICoreGUIApplication
	{
	public:
		ICoreGUIApplication();
		virtual ~ICoreGUIApplication() = 0;

		virtual int Run() = 0;
	};
}
