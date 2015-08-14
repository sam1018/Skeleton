#include "MainWindowImpl.h"
#include <QtWidgets\QApplication>
#include <QtGui\QScreen>
#include <QtWidgets\QComboBox>
#include <QtWidgets\QToolBar>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <iostream>

struct WindowSettings
{
	int m_MonitorIndex;

	void Load(std::string settingsFile)
	{
		namespace pt = boost::property_tree;

		pt::ptree tree;
		pt::read_xml(settingsFile, tree);


		m_MonitorIndex = tree.get("WindowSettings.MonitorIndex", 0);
	}

	void Save(std::string settingsFile)
	{
		namespace pt = boost::property_tree;

		pt::ptree tree;

		tree.put("WindowSettings.MonitorIndex", m_MonitorIndex);

		pt::write_xml(settingsFile, tree);
	}
} g_Settings;

constexpr auto settingsFile{ "../WindowSettings.xml" };

MainWindowImpl::MainWindowImpl() :
	m_Screens{ QApplication::screens() }
{
	g_Settings.Load(settingsFile);

	AddToolbars();
}

MainWindowImpl::~MainWindowImpl()
{
	g_Settings.Save(settingsFile);
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

	if (g_Settings.m_MonitorIndex < 0 || g_Settings.m_MonitorIndex >= m_Screens.size())
	{
		std::cerr << __FUNCTION__ << ": " << g_Settings.m_MonitorIndex << " is not a valid monitor index. Choosing 0 as monitor index.\n";
		g_Settings.m_MonitorIndex = 0;
	}

	comboMonitors->setCurrentIndex(g_Settings.m_MonitorIndex);

	toolbar->addWidget(comboMonitors);

	connect(comboMonitors, SIGNAL(currentIndexChanged(int)), this, SLOT(ShowWindow(int)));
}

void MainWindowImpl::Show()
{
	ShowWindow(g_Settings.m_MonitorIndex);
}

void MainWindowImpl::ShowWindow(int monitorIndex)
{
	showNormal();
	QRect rect = m_Screens[monitorIndex]->availableGeometry();
	move(rect.topLeft());
	showMaximized();
	g_Settings.m_MonitorIndex = monitorIndex;
}
