#pragma once

#include "../SkeletonInterface/ICoreGUIApplication.h"
#include <memory>

class CoreGUIApplication : public GUI::ICoreGUIApplication
{
public:
	CoreGUIApplication(int, char**);
	~CoreGUIApplication();

	int Run();

private:
	struct CoreGUIApplicationImpl;
	std::unique_ptr<CoreGUIApplicationImpl> coreGUIApplicationImpl;
};
