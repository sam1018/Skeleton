#pragma once

#include <functional>
#include <QtCore\QObject>

class QToolBar;
class QLineEdit;

class TBCallControlImpl : public QObject
{
	Q_OBJECT
public:
	TBCallControlImpl();
	~TBCallControlImpl();

	void SetToolbar(QToolBar *tb);
	void Init();
	void SetPlayCallback(std::function<void(double)> PlayCB);
	void SetPauseCallback(std::function<void(void)> PauseCB);
	void SetAchievedCPS(double cps);

signals:
	void SetAchievedCPSSignal(double cps);

	private slots:
	void Play();
	void Pause();
	void SetAchievedCPSHandler(double cps);

private:
	QToolBar *tb;
	QLineEdit *targetCPS;
	QLineEdit *achievedCPS;
	std::function<void(double)> PlayCB;
	std::function<void(void)> PauseCB;
};
