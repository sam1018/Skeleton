#include "TBCallControl.h"
#include "TBCallControlImpl.h"


using namespace std;


TBCallControl::TBCallControl() :
	tbCallControlImpl{ make_unique<TBCallControlImpl>() }
{
}


TBCallControl::~TBCallControl()
{
}

void TBCallControl::SetToolbar(QToolBar *tb)
{
	tbCallControlImpl->SetToolbar(tb);
}

void TBCallControl::Init()
{
	tbCallControlImpl->Init();
}


double TBCallControl::GetTargetCPS_()
{
	return -1;
}

void TBCallControl::SetAchievedCPS_(double cps)
{
	tbCallControlImpl->SetAchievedCPS(cps);
}

void TBCallControl::SetPlayCallback_(std::function<void(double)> PlayCB)
{
	tbCallControlImpl->SetPlayCallback(PlayCB);
}

void TBCallControl::SetPauseCallback_(std::function<void(void)> PauseCB)
{
	tbCallControlImpl->SetPauseCallback(PauseCB);
}
