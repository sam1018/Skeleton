#pragma once

#include <QtWidgets\QApplication.h>
#include "../SkeletonInterface/IOutputWindow.h"


class CoreGUIApplicationImpl : public QApplication
{
public:
	CoreGUIApplicationImpl(int argc, char **argv);
	~CoreGUIApplicationImpl();

	bool notify(QObject * receiver, QEvent * e);

private:
	OutWnd::OutWndCatID outWndId;
};

