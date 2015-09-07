#include "CoreGUIApplication.h"
#include "CoreGUIApplicationImpl.h"
#include "Vitals\IMessagePrinter.h"
#include "Vitals\IVitalsInterfaceManager.h"
#include <QtCore\QTimer>


using namespace VT;
using namespace std;


CoreGUIApplicationImpl::CoreGUIApplicationImpl(int argc, char **argv, CoreGUIApplication *par) :
	QApplication(argc, argv),
	parent{ par }
{
}


CoreGUIApplicationImpl::~CoreGUIApplicationImpl()
{
}


bool CoreGUIApplicationImpl::notify(QObject * receiver, QEvent * e)
{
	using namespace string_literals;

	auto messagePrinter{ GetMessagePrinter() };

	try
	{
		return QApplication::notify(receiver, e);
	}
	catch (exception &ex)
	{
		messagePrinter->PrintMessage(MsgCat_ErrorMsg, ex.what() + "\n"s, true, true);
	}
	catch (...)
	{
		messagePrinter->PrintMessage(MsgCat_ErrorMsg, "Something went wrong.\n", true, true);
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
