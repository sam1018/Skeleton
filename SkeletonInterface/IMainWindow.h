#pragma once

#include "UIItem.h"
#include "SkeletonInterface.h"

namespace MW
{
	SKELETONINTERFACE_DECLSPEC void Show();

	class SKELETONINTERFACE_DECLSPEC IMainWindow : public UI::UIItem
	{
	public:
		IMainWindow();
		virtual ~IMainWindow();

		void InitializeItem();
		void Cleanup();

		virtual void Show() = 0;
	};
}
