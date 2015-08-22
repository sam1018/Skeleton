#include "MainWindowImpl.h"
#include "../SkeletonInterface/Routines.h"
#include <QtCore\QSettings>
#include <QtWidgets\QToolBar>


class QSettingsHelper
{
public:
	QSettingsHelper() :
		settings{ Routines::GetCompanyName().c_str(), Routines::GetApplicationName().c_str() }
	{
	}

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
	QSettings settings;
	const std::string geometryKey{ "geometry" };
	const std::string windowStateKey{ "windowState" };
};


///////////////////////////////////////////////////////////////////////////////
/////////////          MainWindowImpl Definition                   ////////////
///////////////////////////////////////////////////////////////////////////////


MainWindowImpl::MainWindowImpl()
{
	AddToolbars();
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

void MainWindowImpl::AddToolbars()
{
	QToolBar *viewsTB = addToolBar("Views");

	viewsTB->setObjectName("Views TB");
}
