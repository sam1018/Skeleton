#include "SkeletonSettings.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

SkeletonSettings& SkeletonSettings::GetInstance()
{
	static SkeletonSettings theSettings;
	return theSettings;
}

void SkeletonSettings::Load(std::string fileName)
{
	namespace pt = boost::property_tree;
	pt::ptree tree;
	pt::read_xml(fileName, tree);

	m_UIPluginName = tree.get("SkeletonSettings.PluginsList.UIPlugin", "QTUI");
	m_bHideCmdPromptAfterInitialization = tree.get("SkeletonSettings.HideCmdPromptAfterInitialization", false);
}

std::string SkeletonSettings::UIPluginName()
{
	return m_UIPluginName;
}

bool SkeletonSettings::HideCmdPromptAfterInitialization()
{
	return m_bHideCmdPromptAfterInitialization;
}
