#pragma once

#include "../SkeletonInterface/IOutputWindow.h"
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

	void SetupFPS(int fps);

	public slots:
	void Update();

private:
	OutWnd::OutWndCatID outWndId;
	CoreGUIApplication *parent;
};
