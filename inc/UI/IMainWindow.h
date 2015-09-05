#pragma once

#include "SkeletonInterface.h"

namespace UI
{
	class SKELETONINTERFACE_DECLSPEC IMainWindow
	{
	public:
		IMainWindow();
		virtual ~IMainWindow();

		void Show();

	private:
		virtual void Show_() = 0;
	};
}
