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

void IMessagePrinter::PrintMessage(MsgCatID id,
	const string &text, bool append, bool makeCurrrentCategory)
{
	PrintMessage_(id, text, append, makeCurrrentCategory);
}

void IMessagePrinter::SetOutputWindow(IOutputWindow * wnd)
{
	SetOutputWindow_(wnd);
}
