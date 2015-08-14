#include "QTUI.h"
#include <QtWidgets\QApplication.h>
#include "MainWindow.h"
#include <iostream>

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
	QTUI_DECLSPEC bool PluginInitialize(int argc, char** argv)
	{
		try
		{
			g_GlobalData = new QTUIGlobalData(argc, argv);
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << "\n";
			return false;
		}
		catch (...)
		{
			return false;
		}

		return true;
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
