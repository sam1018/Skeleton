#pragma once

#include "UI/ICoreGUIApplication.h"
#include <memory>

class CoreGUIApplicationImpl;

class CoreGUIApplication : public UI::ICoreGUIApplication
{
public:
	CoreGUIApplication(int, char**);
	~CoreGUIApplication();

private:
	virtual int Run_();
	virtual void SetupFPS_(int fps);

private:
	std::unique_ptr<CoreGUIApplicationImpl> coreGUIApplicationImpl;
};
