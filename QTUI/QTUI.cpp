#include "QTUI.h"
#include <QtWidgets\QApplication.h>
#include "MainWindow.h"

struct QTUIGlobalData
{
	std::unique_ptr <QApplication> m_pApp;
	std::unique_ptr <MainWindow> m_pMainWindow;

	QTUIGlobalData(int argc, char** argv) : 
		m_pApp{ std::make_unique<QApplication>(argc, argv) },
		m_pMainWindow{ std::make_unique<MainWindow>() }
	{
	}

	~QTUIGlobalData()
	{
	}

} *g_GlobalData;

extern "C"
{
	QTUI_DECLSPEC void PluginInitialize(int argc, char** argv)
	{
		g_GlobalData = new QTUIGlobalData(argc, argv);
	}
	QTUI_DECLSPEC IMainWindow* GetMainWindow(void)
	{
		return g_GlobalData->m_pMainWindow.get();
	}

	QTUI_DECLSPEC int Run()
	{
		return g_GlobalData->m_pApp->exec();
	}

	QTUI_DECLSPEC void PluginDestroy()
	{
		delete g_GlobalData;
	}
}
