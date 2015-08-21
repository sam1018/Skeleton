#pragma once

#include "SkeletonInterface.h"

namespace GUI
{
	SKELETONINTERFACE_DECLSPEC void Show();

	class SKELETONINTERFACE_DECLSPEC IMainWindow
	{
	public:
		IMainWindow();
		virtual ~IMainWindow();

		virtual void Show() = 0;
	};
}
