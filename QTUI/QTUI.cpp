#include "QTUI.h"
#include "MainWindow.h"
#include "OpenGLWindow.h"
#include "QTUISettings.h"
#include "CoreGUIApplication.h"
#include <memory>


struct QTUIGlobalData
{
	std::unique_ptr <CoreGUIApplication> app;
	std::unique_ptr <OpenGLWindow> openGLWindow;
	std::unique_ptr <MainWindow> mainWindow;

	QTUIGlobalData(int argc, char** argv) :
		app{ std::make_unique<CoreGUIApplication>(argc, argv) },
		openGLWindow{ std::make_unique<OpenGLWindow>() },
		mainWindow{ std::make_unique<MainWindow>(openGLWindow.get()) }
	{
	}

	~QTUIGlobalData()
	{
	}

} *globalData;

constexpr auto settingsFile{ "../QTUISettings.xml" };


// We cannot let this function get inlined
// Or it will create linker error
QTUISettings& GetQTUISettings()
{
	static QTUISettings settings;
	return settings;
}


extern "C"
{
	QTUI_DECLSPEC void PluginInitialize(int argc, char** argv)
	{
		GetQTUISettings().Load(settingsFile);
		globalData = new QTUIGlobalData(argc, argv);
	}

	QTUI_DECLSPEC void PluginDestroy()
	{
		GetQTUISettings().Save(settingsFile);
		delete globalData;
	}
}
