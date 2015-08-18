#include "CoreGUIApplication.h"
#include <QtWidgets\QApplication.h>

struct CoreGUIApplication::CoreGUIApplicationImpl
{
	std::unique_ptr<QApplication> m_pApp;

	CoreGUIApplicationImpl(int argc, char **argv) :
		m_pApp{ std::make_unique<QApplication>(argc, argv) }
	{
	}

	~CoreGUIApplicationImpl()
	{
	}
};

CoreGUIApplication::CoreGUIApplication(int argc, char **argv) :
	m_pImpl{ std::make_unique<CoreGUIApplicationImpl>(argc, argv) }
{
}


CoreGUIApplication::~CoreGUIApplication()
{
}

int CoreGUIApplication::Run()
{
	return m_pImpl->m_pApp->exec();
}
