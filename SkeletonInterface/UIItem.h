#pragma once

#include "SkeletonInterface.h"
#include <string>

namespace UI
{
	void SKELETONINTERFACE_DECLSPEC InitializeItems();
	void SKELETONINTERFACE_DECLSPEC Cleanup();

	class SKELETONINTERFACE_DECLSPEC UIItem
	{
	public:
		UIItem();
		virtual ~UIItem() = 0;

		virtual void InitializeItem() = 0;
		virtual void Cleanup() = 0;
	};
}
