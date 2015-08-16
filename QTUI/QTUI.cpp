#include "QTUI.h"
#include <iostream>

QTUIGlobalData *g_GlobalData = nullptr;

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

	QTUI_DECLSPEC IOpenGLWindow* GetOpenGLWindow(void)
	{
		return g_GlobalData->m_pOpenGLWindow.get();
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
