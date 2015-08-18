#include "QTGUISettings.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

QTGUISettings& QTGUISettings::GetInstance()
{
	static QTGUISettings theQTGUISettings;
	return theQTGUISettings;
}

void QTGUISettings::Load(std::string fileName)
{
	namespace pt = boost::property_tree;

	pt::ptree tree;
	pt::read_xml(fileName, tree);


	m_MonitorIndex = tree.get("QTGUISettings.MonitorIndex", 0);
}

void QTGUISettings::Save(std::string settingsFile)
{
	namespace pt = boost::property_tree;

	pt::ptree tree;

	tree.put("QTGUISettings.MonitorIndex", m_MonitorIndex);

	pt::write_xml(settingsFile, tree);
}

int QTGUISettings::GetMonitorIndex()
{
	return m_MonitorIndex;
}

void QTGUISettings::SetMonitorIndex(int nMonitorIndex)
{
	m_MonitorIndex = nMonitorIndex;
}
