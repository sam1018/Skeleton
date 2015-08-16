#pragma once

#include "OpenGLWindow.h"
#include <memory>
#include <QtWidgets\QApplication.h>
#include "MainWindow.h"

#ifdef QTUI_EXPORTS
#define QTUI_DECLSPEC    __declspec(dllexport)
#else
#define QTUI_DECLSPEC    __declspec(dllimport)
#endif

struct QTUIGlobalData
{
	std::unique_ptr <QApplication> m_pApp;
	std::unique_ptr <OpenGLWindow> m_pOpenGLWindow;
	std::unique_ptr <MainWindow> m_pMainWindow;

	QTUIGlobalData(int argc, char** argv) :
		m_pApp{ std::make_unique<QApplication>(argc, argv) },
		m_pOpenGLWindow{ std::make_unique<OpenGLWindow>() },
		m_pMainWindow{ std::make_unique<MainWindow>(m_pOpenGLWindow.get()) }
	{
	}

	~QTUIGlobalData()
	{
	}

};

extern QTUIGlobalData *g_GlobalData;
