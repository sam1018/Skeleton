#include "MainWindowImpl.h"
#include "Routines.h"
#include <QtCore\QSettings>
#include <QtWidgets\QToolBar>

using namespace std;
using namespace Routines;


class QSettingsHelper
{
public:
	static QSettingsHelper& GetInstance()
	{
		static QSettingsHelper theQSettingsHelper;
		return theQSettingsHelper;
	}

	void Save(MainWindowImpl *mainWindowImpl)
	{
		settings.setValue(geometryKey.c_str(), mainWindowImpl->saveGeometry());
		settings.setValue(windowStateKey.c_str(), mainWindowImpl->saveState());
	}

	void Load(MainWindowImpl *mainWindowImpl)
	{
		mainWindowImpl->restoreGeometry(settings.value(geometryKey.c_str()).toByteArray());
		mainWindowImpl->restoreState(settings.value(windowStateKey.c_str()).toByteArray());
	}

	bool HasGeometryInfo()
	{
		return settings.contains(geometryKey.c_str());
	}

private:
	QSettingsHelper() :
		settings{ GetCompanyName().c_str(), GetApplicationName().c_str() }
	{
	}

private:
	QSettings settings;
	const string geometryKey{ "geometry" };
	const string windowStateKey{ "windowState" };
};


///////////////////////////////////////////////////////////////////////////////
/////////////          MainWindowImpl Definition                   ////////////
///////////////////////////////////////////////////////////////////////////////


MainWindowImpl::MainWindowImpl()
{
	//AddToolbars();
}

MainWindowImpl::~MainWindowImpl()
{
}

void MainWindowImpl::Show()
{
	if (QSettingsHelper::GetInstance().HasGeometryInfo())
	{
		QSettingsHelper::GetInstance().Load(this);
		show();
	}
	else
		showMaximized();
}

void MainWindowImpl::closeEvent(QCloseEvent *event)
{
	QSettingsHelper::GetInstance().Save(this);
	QMainWindow::closeEvent(event);
}
