#pragma once

#include "../SkeletonInterface/ICoreGUIApplication.h"
#include <memory>

class CoreGUIApplication : public CGA::ICoreGUIApplication
{
public:
	CoreGUIApplication(int, char**);
	~CoreGUIApplication();

	int Run();

private:
	struct CoreGUIApplicationImpl;
	std::unique_ptr<CoreGUIApplicationImpl> m_pImpl;
};
