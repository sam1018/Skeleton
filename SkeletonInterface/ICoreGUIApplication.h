#pragma once

#include "UIItem.h"
#include "SkeletonInterface.h"

namespace CGA
{
	SKELETONINTERFACE_DECLSPEC int Run();

	class SKELETONINTERFACE_DECLSPEC ICoreGUIApplication : public UI::UIItem
	{
	public:
		ICoreGUIApplication();
		virtual ~ICoreGUIApplication() = 0;

		void InitializeItem();
		void Cleanup();

		virtual int Run() = 0;
	};
}
