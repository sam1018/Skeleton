#pragma once

#include <memory>
#include <string>

class IMainFrame;

// Singleton class, contains core logic
class World
{
private:
	World();
	~World();

public:
	static World& GetInstance();

	void LoadPlugins(std::string fileName);

	void LoadObjects();

private:
	IMainFrame* CreateMainFrame();

private:
	struct ImplData;
	std::unique_ptr <ImplData> m_pImplData;
};
