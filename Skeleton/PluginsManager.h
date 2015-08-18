#pragma once

#include <memory>
#include <string>

enum class PluginType
{
	QTUI,
	TOTAL
};

constexpr int PluginTypeCount()
{
	return static_cast<int>(PluginType::TOTAL);
}

constexpr int PluginIndex(PluginType pluginType)
{
	return static_cast<int>(pluginType);
}

class PluginsManager
{
public:
	PluginsManager();
	~PluginsManager();

	void LoadPlugins();

	void Initialize(int argc, char **argv);

private:
	struct PluginsManagerImpl;
	std::unique_ptr <PluginsManagerImpl> m_pImpl;
};
