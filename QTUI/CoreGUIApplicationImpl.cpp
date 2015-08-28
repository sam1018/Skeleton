#include "CoreGUIApplicationImpl.h"

CoreGUIApplicationImpl::CoreGUIApplicationImpl(int argc, char **argv) :
	QApplication(argc, argv),
	outWndId{ OutWnd::RegisterOutputWindowCategory(OutWnd::OutWndErrorMssgCategory) }
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
	catch (std::exception &e)
	{
		OutWnd::OutputWindowSetText(outWndId, e.what() + "\n"s, true, true);
	}
	catch (...)
	{
		OutWnd::OutputWindowSetText(outWndId, "Something went wrong.\n", true, true);
	}

	return false;
}
