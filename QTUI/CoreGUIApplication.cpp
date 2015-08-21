#include "CoreGUIApplication.h"
#include <QtWidgets\QApplication.h>

///////////////////////////////////////////////////////////////////////////////
/////////////          CoreGUIApplication Definition               ////////////
///////////////////////////////////////////////////////////////////////////////

struct CoreGUIApplication::CoreGUIApplicationImpl
{
	std::unique_ptr<QApplication> app;

	CoreGUIApplicationImpl(int argc, char **argv) :
		app{ std::make_unique<QApplication>(argc, argv) }
	{
	}

	~CoreGUIApplicationImpl()
	{
	}
};

CoreGUIApplication::CoreGUIApplication(int argc, char **argv) :
	coreGUIApplicationImpl{ std::make_unique<CoreGUIApplicationImpl>(argc, argv) }
{
}


CoreGUIApplication::~CoreGUIApplication()
{
}

int CoreGUIApplication::Run()
{
	return coreGUIApplicationImpl->app->exec();
}
