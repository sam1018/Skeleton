#pragma once

#include <string>

class SkeletonSettings
{
public:
	static SkeletonSettings& GetInstance();
	void Load(std::string fileName);

	// Query Functions
	std::string UIPluginName();
	bool HideCmdPromptAfterInitialization();

private:
	std::string m_UIPluginName;
	bool m_bHideCmdPromptAfterInitialization;
};
