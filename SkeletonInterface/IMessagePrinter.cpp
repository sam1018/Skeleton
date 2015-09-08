#include "Vitals\IMessagePrinter.h"

using namespace UI;
using namespace VT;
using namespace std;


MsgCatID VT::MsgCat_PluginExplorer;
MsgCatID VT::MsgCat_ErrorMsg;



IRedirHandler::~IRedirHandler()
{
}

void IRedirHandler::Pause()
{
	Pause_();
}

void IRedirHandler::Resume()
{
	Resume_();
}




IMessagePrinter::IMessagePrinter()
{
}

IMessagePrinter::~IMessagePrinter()
{
}

MsgCatID IMessagePrinter::RegisterMessageCategory(const string &categoryName)
{
	return RegisterMessageCategory_(categoryName);
}

void IMessagePrinter::PrintMessage(MsgCatID id, const string &text, bool append, 
	bool makeCurrrentCategory, const char *file, int line)
{
	PrintMessage_(id, text, append, makeCurrrentCategory, file, line);
}

void IMessagePrinter::SetOutputWindow(IOutputWindow * wnd)
{
	SetOutputWindow_(wnd);
}

std::unique_ptr<IRedirHandler> IMessagePrinter::RedirectStream(std::ostream & stream, MsgCatID cat)
{
	return RedirectStream_(stream, cat);
}
