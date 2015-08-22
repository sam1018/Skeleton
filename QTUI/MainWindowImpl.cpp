#include "MainWindowImpl.h"
#include "QTUISettings.h"
#include <iostream>
#include <QtGui\QScreen>
#include <QtWidgets\QToolBar>
#include <QtWidgets\QComboBox>
#include <QtWidgets\QApplication>


///////////////////////////////////////////////////////////////////////////////
/////////////          MainWindowImpl Definition                   ////////////
///////////////////////////////////////////////////////////////////////////////


MainWindowImpl::MainWindowImpl() :
	screens{ QApplication::screens() }
{
	AddToolbars();
}

MainWindowImpl::~MainWindowImpl()
{
}

void MainWindowImpl::AddToolbars()
{
	QToolBar *viewsTB = addToolBar("Views");

	AddTBBMonitors(viewsTB);
}

void MainWindowImpl::AddTBBMonitors(QToolBar *toolbar)
{
	QComboBox *comboMonitors = new QComboBox;

	for (auto* screen : screens)
		comboMonitors->addItem("Monitor: " + screen->name());

	if (GetQTUISettings().monitorIndex < 0 || GetQTUISettings().monitorIndex >= screens.size())
	{
		std::cerr << __FUNCTION__ << ": " << GetQTUISettings().monitorIndex << " is not a valid monitor index. Choosing 0 as monitor index.\n";
		GetQTUISettings().monitorIndex = 0;
	}

	comboMonitors->setCurrentIndex(GetQTUISettings().monitorIndex);

	toolbar->addWidget(comboMonitors);

	connect(comboMonitors, SIGNAL(currentIndexChanged(int)), this, SLOT(ShowWindow(int)));
}

void MainWindowImpl::Show()
{
	ShowWindow(GetQTUISettings().monitorIndex);
}

void MainWindowImpl::ShowWindow(int monitorIndex)
{
	showNormal();
	QRect rect = screens[monitorIndex]->availableGeometry();
	move(rect.topLeft());
	showMaximized();
	GetQTUISettings().monitorIndex = monitorIndex;
}
