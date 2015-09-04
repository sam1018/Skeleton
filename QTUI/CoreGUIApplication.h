#pragma once

#include "UI/ICoreGUIApplication.h"
#include <memory>

class CoreGUIApplicationImpl;

class CoreGUIApplication : public CGA::ICoreGUIApplication
{
public:
	CoreGUIApplication(int, char**);
	~CoreGUIApplication();

	void* GetImpl();

	int Run();

	void SetupFPS(int fps);

private:
	std::unique_ptr<CoreGUIApplicationImpl> coreGUIApplicationImpl;
};
