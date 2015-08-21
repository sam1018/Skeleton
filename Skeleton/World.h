#pragma once

#include <memory>
#include <string>

class IMainWindow;

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
	struct WorldImpl;
	std::unique_ptr <WorldImpl> worldImpl;
};
