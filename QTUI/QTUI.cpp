#include "QTUI.h"
#include <memory>
#include "OpenGLWindow.h"
#include "MainWindow.h"
#include "CoreGUIApplication.h"
#include "QTGUISettings.h"


struct QTUIGlobalData
{
	std::unique_ptr <CoreGUIApplication> m_pApp;
	std::unique_ptr <OpenGLWindow> m_pOpenGLWindow;
	std::unique_ptr <MainWindow> m_pMainWindow;

	QTUIGlobalData(int argc, char** argv) :
		m_pApp{ std::make_unique<CoreGUIApplication>(argc, argv) },
		m_pOpenGLWindow{ std::make_unique<OpenGLWindow>() },
		m_pMainWindow{ std::make_unique<MainWindow>(m_pOpenGLWindow.get()) }
	{
	}

	~QTUIGlobalData()
	{
	}

} *g_GlobalData;

constexpr auto settingsFile{ "../QTGUISettings.xml" };

extern "C"
{
	QTUI_DECLSPEC void PluginInitialize(int argc, char** argv)
	{
		QTGUISettings::GetInstance().Load(settingsFile);
		g_GlobalData = new QTUIGlobalData(argc, argv);
	}

	QTUI_DECLSPEC void PluginDestroy()
	{
		QTGUISettings::GetInstance().Save(settingsFile);
		delete g_GlobalData;
	}
}
