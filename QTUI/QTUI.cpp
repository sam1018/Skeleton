#include "QTUI.h"
#include <QtWidgets\QApplication.h>
#include "MainWindow.h"

struct QTUIGlobalData
{
	QApplication *m_pApp = nullptr;
	MainWindow *m_pMainWindow = nullptr;

	void Initialize(int argc, char** argv)
	{
		m_pApp = new QApplication(argc, argv);
		m_pMainWindow = new MainWindow;
	}

	void Destroy()
	{
		delete m_pMainWindow;
		delete m_pApp;
	}

}g_GlobalData;

extern "C"
{
	QTUI_DECLSPEC void PluginInitialize(int argc, char** argv)
	{
		g_GlobalData.Initialize(argc, argv);
	}
	QTUI_DECLSPEC IMainWindow* GetMainWindow(void)
	{
		return g_GlobalData.m_pMainWindow;
	}

	QTUI_DECLSPEC void PluginDestroy()
	{
		g_GlobalData.Destroy();
	}
}
