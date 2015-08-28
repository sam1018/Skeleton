#pragma once

#include "../SkeletonInterface/ICoreGUIApplication.h"
#include <memory>

class CoreGUIApplicationImpl;

class CoreGUIApplication : public CGA::ICoreGUIApplication
{
public:
	CoreGUIApplication(int, char**);
	~CoreGUIApplication();

	void* GetImpl();

	int Run();

private:
	std::unique_ptr<CoreGUIApplicationImpl> coreGUIApplicationImpl;
};
