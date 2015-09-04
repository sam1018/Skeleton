#pragma once

#include <memory>
#include <string>


class World
{
public:
	World(int argc, char** argv);
	~World();

	void Initialize() const;

	void Show() const;

	int Run() const;

	void Cleanup() const;

	bool IsHideCmdPromptAfterInitialization() const;

private:
	struct WorldImpl;
	std::unique_ptr<WorldImpl> worldImpl;
};
