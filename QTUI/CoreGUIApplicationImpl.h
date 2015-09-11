#pragma once

#include <functional>
#include <QtWidgets\QApplication.h>

class CoreGUIApplication;

class CoreGUIApplicationImpl : public QApplication
{
	Q_OBJECT

public:
	CoreGUIApplicationImpl(int argc, char **argv, CoreGUIApplication *parent);
	~CoreGUIApplicationImpl();

	bool notify(QObject * receiver, QEvent * e);

	//void SetupFPS(int fps);

	//public slots:
	//void Update();

private:
	CoreGUIApplication *parent;
};
