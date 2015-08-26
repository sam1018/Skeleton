#include "ICoreGUIApplication.h"

using namespace CGA;

ICoreGUIApplication *coreGUIApplication;


void ThrowUninitializedClass(std::string className)
{
	throw std::exception((className + " class is not initialized").c_str());
}


int CGA::Run()
{
	if (!coreGUIApplication)
		ThrowUninitializedClass("ICoreGUIApplication");

	return coreGUIApplication->Run();
}

///////////////////////////////////////////////////////////////////////////////
/////////////          ICoreGUIApplication Definition              ////////////
///////////////////////////////////////////////////////////////////////////////

ICoreGUIApplication::ICoreGUIApplication()
{
}

ICoreGUIApplication::~ICoreGUIApplication()
{
}

void ICoreGUIApplication::InitializeItem()
{
	coreGUIApplication = this;
}

void ICoreGUIApplication::Cleanup()
{
	coreGUIApplication = nullptr;
}
