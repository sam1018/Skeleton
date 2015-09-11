#include "UI\ITBCallControl.h"
#include "Vitals\ICallerManager.h"
#include "Vitals\IVitalsInterfaceManager.h"

using namespace UI;
using namespace VT;


ITBCallControl::~ITBCallControl()
{
	GetCallerManager()->SetAchievedCPSCallback(nullptr);
}


double ITBCallControl::GetTargetCPS()
{
	return GetTargetCPS_();
}

void ITBCallControl::SetAchievedCPS(double cps)
{
	SetAchievedCPS_(cps);
}

void UI::ITBCallControl::Init()
{
	ICallerManager *cm = GetCallerManager();

	SetPlayCallback_(cm->CallbackPlay());
	SetPauseCallback_(cm->CallbackPause());
	cm->SetAchievedCPSCallback([this](double cps) { SetAchievedCPS(cps); });
}
