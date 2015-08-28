#include "CoreGUIApplication.h"
#include "CoreGUIApplicationImpl.h"


///////////////////////////////////////////////////////////////////////////////
/////////////          CoreGUIApplication Definition               ////////////
///////////////////////////////////////////////////////////////////////////////


CoreGUIApplication::CoreGUIApplication(int argc, char **argv) :
	coreGUIApplicationImpl{ std::make_unique<CoreGUIApplicationImpl>(argc, argv) }
{
}


CoreGUIApplication::~CoreGUIApplication()
{
}

void* CoreGUIApplication::GetImpl()
{
	return coreGUIApplicationImpl.get();
}

int CoreGUIApplication::Run()
{
	return coreGUIApplicationImpl->exec();
}
