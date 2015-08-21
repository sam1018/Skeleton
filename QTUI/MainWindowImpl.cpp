#include "MainWindowImpl.h"
#include "QTUI.h"
#include "OpenGLWindow.h"
#include "QTGUISettings.h"
#include <QtWidgets\QApplication>
#include <QtGui\QScreen>
#include <QtWidgets\QComboBox>
#include <QtWidgets\QToolBar>
#include <iostream>

MainWindowImpl::MainWindowImpl(OpenGLWindow *pOpenGLWindow) :
	m_Screens{ QApplication::screens() }
{
	setCentralWidget(QWidget::createWindowContainer(pOpenGLWindow->GetOpenGLWindowImpl()));

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

	for (auto* screen : m_Screens)
		comboMonitors->addItem("Monitor: " + screen->name());

	int nMonitorIndex = QTGUISettings::GetInstance().m_MonitorIndex;

	if (nMonitorIndex < 0 || nMonitorIndex >= m_Screens.size())
	{
		std::cerr << __FUNCTION__ << ": " << nMonitorIndex << " is not a valid monitor index. Choosing 0 as monitor index.\n";
		QTGUISettings::GetInstance().m_MonitorIndex = 0;
	}

	comboMonitors->setCurrentIndex(QTGUISettings::GetInstance().m_MonitorIndex);

	toolbar->addWidget(comboMonitors);

	connect(comboMonitors, SIGNAL(currentIndexChanged(int)), this, SLOT(ShowWindow(int)));
}

void MainWindowImpl::Show()
{
	ShowWindow(QTGUISettings::GetInstance().m_MonitorIndex);
}

void MainWindowImpl::ShowWindow(int monitorIndex)
{
	showNormal();
	QRect rect = m_Screens[monitorIndex]->availableGeometry();
	move(rect.topLeft());
	showMaximized();
	QTGUISettings::GetInstance().m_MonitorIndex = monitorIndex;
}
