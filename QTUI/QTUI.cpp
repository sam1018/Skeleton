#include "QTUI.h"
#include "MainWindow.h"
#include "OpenGLWindow.h"
#include "QTUISettings.h"
#include "CoreGUIApplication.h"
#include "Routines.h"
#include "OpenGLWindow.h"
#include "UI\IUIInterfaceManager.h"
#include "CommonControls.h"
#include <memory>


class UIInterfaceManager : public UI::IUIInterfaceManager
{
public:
	UIInterfaceManager(int argc, char** argv) :
		app{ std::make_unique<CoreGUIApplication>(argc, argv) },
		commonControls{ std::make_unique<CommonControls>() },
		openGLWindow{ std::make_unique<OpenGLWindow>() },
		mainWindow{ std::make_unique<MainWindow>(openGLWindow.get()) }
	{
	}

	virtual ~UIInterfaceManager()
	{
	}

private:
	virtual UI::ICommonControls* GetCommonControls()
	{
		return commonControls.get();
	}

	virtual UI::ICoreGUIApplication* GetCoreGUIApplication()
	{
		return app.get();
	}

	virtual UI::IMainWindow* GetMainWindow()
	{
		return mainWindow.get();
	}

	virtual UI::IOpenGLWindow* GetOpenGLWindow()
	{
		return openGLWindow.get();
	}

private:
	std::unique_ptr <CoreGUIApplication> app;
	std::unique_ptr<CommonControls> commonControls;
	std::unique_ptr<OpenGLWindow> openGLWindow;
	std::unique_ptr <MainWindow> mainWindow;

} *uiInterfaceManager;

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
		uiInterfaceManager = new UIInterfaceManager(argc, argv);
	}

	QTUI_DECLSPEC UI::IUIInterfaceManager* GetInterfaceManager()
	{
		return uiInterfaceManager;
	}

	QTUI_DECLSPEC void DestroyModule()
	{
		GetQTUISettings().Save(Routines::GetSettingsFileFullPath_Save(settingsFile));
		delete uiInterfaceManager;
	}
}
