#include "TBCallControlImpl.h"
#include <QtWidgets\QStyle>
#include <QtWidgets\QToolBar>
#include <QtWidgets\QLineEdit>
#include <QtGui\QDoubleValidator>


TBCallControlImpl::TBCallControlImpl()
{
}


TBCallControlImpl::~TBCallControlImpl()
{
}

void TBCallControlImpl::SetToolbar(QToolBar *tb_)
{
	tb = tb_;
}

void TBCallControlImpl::Init()
{
	tb->setObjectName("TBCallControl");

	targetCPS = new QLineEdit;
	targetCPS->setMaximumWidth(50);
	targetCPS->setValidator(new QDoubleValidator(0, 1000, 4));
	targetCPS->setToolTip("Target calls per second");
	targetCPS->setText("60");
	tb->addWidget(targetCPS);

	tb->addAction(tb->style()->standardIcon(QStyle::SP_MediaPlay), "", this, SLOT(Play()));
	tb->addAction(tb->style()->standardIcon(QStyle::SP_MediaPause), "", this, SLOT(Pause()));

	achievedCPS = new QLineEdit;
	achievedCPS->setMaximumWidth(50);
	achievedCPS->setToolTip("Achieved calls per second");
	achievedCPS->setText("0");
	achievedCPS->setReadOnly(true);
	tb->addWidget(achievedCPS);

	// As SetAchievedCPS function will be called from outside GUI thread
	// So we need to do the following dance
	connect(this, SIGNAL(SetAchievedCPSSignal(double)), this, SLOT(SetAchievedCPSHandler(double)));
}

void TBCallControlImpl::SetPlayCallback(std::function<void(double)> PlayCB_)
{
	PlayCB = PlayCB_;
}

void TBCallControlImpl::SetPauseCallback(std::function<void(void)> PauseCB_)
{
	PauseCB = PauseCB_;
}

void TBCallControlImpl::SetAchievedCPS(double cps)
{
	emit SetAchievedCPSSignal(cps);
}

void TBCallControlImpl::SetAchievedCPSHandler(double cps)
{
	achievedCPS->setText(QString::number(cps));
}

void TBCallControlImpl::Play()
{
	PlayCB(targetCPS->text().toDouble());
}

void TBCallControlImpl::Pause()
{
	PauseCB();
}
