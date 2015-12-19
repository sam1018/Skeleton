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

	try
	{
		return QApplication::notify(receiver, e);
	}
	catch (exception &ex)
	{
		PRINT_MESSAGE(MsgCat_ErrorMsg, ex.what() + "\n"s, true, true)
	}
	catch (...)
	{
		PRINT_MESSAGE(MsgCat_ErrorMsg, "Something went wrong.\n", true, true)
	}

	return false;
}
