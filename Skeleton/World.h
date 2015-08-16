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

	void LoadSettings(std::string fileName);

	void LoadPlugins();

	void LoadObjects();

	void Arguements(int argc, char** argv);

	void Show();

	int Run();

	bool HideCmdPromptAfterInitialization();

private:
	struct ImplData;
	std::unique_ptr <ImplData> m_pImplData;
	int m_argc;
	char** m_argv;
};
