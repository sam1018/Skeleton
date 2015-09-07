#include "Vitals\IMessagePrinter.h"

using namespace UI;
using namespace VT;
using namespace std;


MsgCatID VT::MsgCat_PluginExplorer;
MsgCatID VT::MsgCat_ErrorMsg;

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
