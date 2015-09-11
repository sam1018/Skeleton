#include "QTUI.h"
#include "Routines.h"
#include "MainWindow.h"
#include "OpenGLWindow.h"
#include "QTUISettings.h"
#include "OpenGLWindow.h"
#include "OutputWindow.h"
#include "CommonControls.h"
#include "CoreGUIApplication.h"
#include "TBCallControl.h"
#include "UI\IUIInterfaceManager.h"
#include <memory>

using namespace UI;
using namespace std;
using namespace Routines;


class UIInterfaceManager : public IUIInterfaceManager
{
public:
	UIInterfaceManager(int argc, char** argv) :
		app{ make_unique<CoreGUIApplication>(argc, argv) },
		commonControls{ make_unique<CommonControls>() },
		openGLWindow{ make_unique<OpenGLWindow>() },
		outputWindow{ make_unique<OutputWindow>() },
		tbCallControl{ make_unique<TBCallControl>() },
		mainWindow{ make_unique<MainWindow>(openGLWindow.get(), outputWindow.get(),
			tbCallControl.get()) }
	{
		tbCallControl->Init();
	}

	virtual ~UIInterfaceManager()
	{
	}

private:
	virtual ICommonControls* GetCommonControls()
	{
		return commonControls.get();
	}

	virtual ICoreGUIApplication* GetCoreGUIApplication()
	{
		return app.get();
	}

	virtual IMainWindow* GetMainWindow()
	{
		return mainWindow.get();
	}

	virtual IOpenGLWindow* GetOpenGLWindow()
	{
		return openGLWindow.get();
	}

	virtual IOutputWindow* GetOutputWindow()
	{
		return outputWindow.get();
	}

	virtual ITBCallControl* GetTBCallControl()
	{
		return tbCallControl.get();
	}

private:
	unique_ptr <CoreGUIApplication> app;
	unique_ptr<CommonControls> commonControls;
	unique_ptr<OpenGLWindow> openGLWindow;
	unique_ptr<OutputWindow> outputWindow;
	unique_ptr <TBCallControl> tbCallControl;
	unique_ptr <MainWindow> mainWindow;

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
		GetQTUISettings().Load(GetSettingsFileFullPath_Load(settingsFile));
		uiInterfaceManager = new UIInterfaceManager(argc, argv);
	}

	QTUI_DECLSPEC IUIInterfaceManager* GetInterfaceManager()
	{
		return uiInterfaceManager;
	}

	QTUI_DECLSPEC void DestroyModule()
	{
		GetQTUISettings().Save(GetSettingsFileFullPath_Save(settingsFile));
		delete uiInterfaceManager;
	}
}
