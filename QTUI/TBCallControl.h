#pragma once


#include "UI\ITBCallControl.h"
#include <memory>

class QToolBar;
class TBCallControlImpl;

class TBCallControl : public UI::ITBCallControl
{
public:
	TBCallControl();
	virtual ~TBCallControl();

	void SetToolbar(QToolBar *tb);

	void Init();

private:
	virtual double GetTargetCPS_();
	virtual void SetAchievedCPS_(double cps);
	virtual void SetPlayCallback_(std::function<void(double)> PlayCB);
	virtual void SetPauseCallback_(std::function<void(void)> PauseCB);

private:
	std::unique_ptr<TBCallControlImpl> tbCallControlImpl;
};
