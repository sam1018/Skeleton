#pragma once

#include <memory>
#include <string>

class IMainWindow;

// Singleton class, contains core logic
class World
{
private:
	World();
	~World();

public:
	static World& GetInstance();

	void InitializePlugins(int argc, char** argv);

	void Show();

	int Run();

private:
	struct ImplData;
	std::unique_ptr <ImplData> m_pImplData;
};
