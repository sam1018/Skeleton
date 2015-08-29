#include "CoreGUIApplication.h"
#include "CoreGUIApplicationImpl.h"
#include <QtCore\QTimer>

CoreGUIApplicationImpl::CoreGUIApplicationImpl(int argc, char **argv, CoreGUIApplication *par) :
	QApplication(argc, argv),
	outWndId{ OutWnd::RegisterOutputWindowCategory(OutWnd::OutWndErrorMssgCategory) },
	parent{ par }
{
}


CoreGUIApplicationImpl::~CoreGUIApplicationImpl()
{
}


bool CoreGUIApplicationImpl::notify(QObject * receiver, QEvent * e)
{
	using namespace std::string_literals;

	try
	{
		return QApplication::notify(receiver, e);
	}
	catch (std::exception &ex)
	{
		OutWnd::OutputWindowSetText(outWndId, ex.what() + "\n"s, true, true);
	}
	catch (...)
	{
		OutWnd::OutputWindowSetText(outWndId, "Something went wrong.\n", true, true);
	}

	return false;
}

void CoreGUIApplicationImpl::SetupFPS(int fps)
{
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(Update()));
	timer->start(1000 / fps);
}

void CoreGUIApplicationImpl::Update()
{
	parent->FPSHandler();
}
