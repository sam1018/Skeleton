#include "ICoreGUIApplication.h"

using namespace GUI;

ICoreGUIApplication *coreGUIApplication;


void ThrowUninitializedClass(std::string className)
{
	throw std::exception((className + " class is not initialized").c_str());
}


int GUI::Run()
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
	coreGUIApplication = this;
}

ICoreGUIApplication::~ICoreGUIApplication()
{
	coreGUIApplication = nullptr;
}
