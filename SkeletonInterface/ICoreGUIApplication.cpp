#include "ICoreGUIApplication.h"

using namespace GUI;

ICoreGUIApplication *m_pCoreGUIApplication;

ICoreGUIApplication::ICoreGUIApplication()
{
	m_pCoreGUIApplication = this;
}


ICoreGUIApplication::~ICoreGUIApplication()
{
	m_pCoreGUIApplication = nullptr;
}

int GUI::Run()
{
	if (!m_pCoreGUIApplication)
		ThrowUninitializedClass("ICoreGUIApplication");

	return m_pCoreGUIApplication->Run();
}
