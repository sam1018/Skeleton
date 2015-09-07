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

//void MainWindowImpl::AddToolbars()
//{
//	QToolBar *outputWindowTest = addToolBar("OutputWindowTest");
//
//	outputWindowTest->setObjectName("OutputWindowTest");
//
//	outputWindowTest->addAction("AddCatDebug", this, SLOT(AddCatDebug()));
//	outputWindowTest->addAction("AppendToDebug", this, SLOT(AppendToDebug()));
//	outputWindowTest->addAction("AddCatDebug2", this, SLOT(AddCatDebug2()));
//	outputWindowTest->addAction("AppendToDebug2", this, SLOT(AppendToDebug2()));
//}

//#include "../SkeletonInterface/IOutputWindow.h"
//
//OutWnd::MsgCatID debugID;
//OutWnd::MsgCatID debugID2;
//void MainWindowImpl::AddCatDebug()
//{
//	debugID = OutWnd::RegisterOutputWindowCategory("Debug");
//}
//
//void MainWindowImpl::AppendToDebug()
//{
//	static int x = 0;
//	OutWnd::OutputWindowSetText(debugID, (string("Some Text: ") + to_string(x++)), true, true);
//}
//
//void MainWindowImpl::AddCatDebug2()
//{
//	debugID2 = OutWnd::RegisterOutputWindowCategory("Debug 2");
//}
//
//void MainWindowImpl::AppendToDebug2()
//{
//	static int x = 0;
//	OutWnd::OutputWindowSetText(debugID2, (string("Some Some Other Text XXXXXXXXXXXXXXXXXXXX Text: ") + to_string(x++)), true, true);
//}
