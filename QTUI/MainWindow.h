#pragma once

#include <QtWidgets\qmainwindow.h>
#include "../SkeletonInterface/IMainWindow.h"

class MainWindow : public QMainWindow, public IMainWindow
{
public:
	MainWindow();
	~MainWindow();
};
