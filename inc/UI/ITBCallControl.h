#pragma once

#include "SkeletonInterface.h"
#include <functional>

namespace UI
{
	class SKELETONINTERFACE_DECLSPEC ITBCallControl
	{
	public:
		virtual ~ITBCallControl() = 0;

		double GetTargetCPS();

		// Will be called from outside GUI thread
		void SetAchievedCPS(double cps);
		void Init();

	private:
		virtual double GetTargetCPS_() = 0;
		virtual void SetAchievedCPS_(double cps) = 0;
		virtual void SetPlayCallback_(std::function<void(double)> PlayCB) = 0;
		virtual void SetPauseCallback_(std::function<void(void)> PauseCB) = 0;
	};
}
