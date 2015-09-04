#include "QTUI.h"
#include "MainWindow.h"
#include "OpenGLWindow.h"
#include "QTUISettings.h"
#include "CoreGUIApplication.h"
#include "Routines.h"
#include "UI\IUIInterfaceManager.h"
#include <memory>


struct QTUIGlobalData
{
	std::unique_ptr <CoreGUIApplication> app;
	std::unique_ptr <MainWindow> mainWindow;

	QTUIGlobalData(int argc, char** argv) :
		app{ std::make_unique<CoreGUIApplication>(argc, argv) },
		mainWindow{ std::make_unique<MainWindow>() }
	{
	}

	~QTUIGlobalData()
	{
	}

} *globalData;

class UIInterfaceManager : public UI::IUIInterfaceManager
{} uiInterfaceManager;

constexpr auto settingsFile{ "QTUISettings.xml" };


// We cannot let this function get inlined
// Or it will create linker error
QTUISettings& GetQTUISettings()
{
	static QTUISettings settings;
	return settings;
}


extern "C"
{
	QTUI_DECLSPEC void InitializeModule(int argc, char** argv, int)
	{
		GetQTUISettings().Load(Routines::GetSettingsFileFullPath_Load(settingsFile));
		globalData = new QTUIGlobalData(argc, argv);
	}

	QTUI_DECLSPEC UI::IUIInterfaceManager* GetInterfaceManager()
	{
		return &uiInterfaceManager;
	}

	QTUI_DECLSPEC void DestroyModule()
	{
		GetQTUISettings().Save(Routines::GetSettingsFileFullPath_Save(settingsFile));
		delete globalData;
	}
}
