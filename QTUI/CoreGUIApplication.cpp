#include "CoreGUIApplication.h"
#include "CoreGUIApplicationImpl.h"


///////////////////////////////////////////////////////////////////////////////
/////////////          CoreGUIApplication Definition               ////////////
///////////////////////////////////////////////////////////////////////////////


CoreGUIApplication::CoreGUIApplication(int argc, char **argv) :
	coreGUIApplicationImpl{ std::make_unique<CoreGUIApplicationImpl>(argc, argv, this) }
{
}


CoreGUIApplication::~CoreGUIApplication()
{
}

int CoreGUIApplication::Run_()
{
	return coreGUIApplicationImpl->exec();
}

void CoreGUIApplication::SetupFPS_(int fps)
{
	coreGUIApplicationImpl->SetupFPS(fps);
}
