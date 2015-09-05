#include "Vitals\IMessagePrinter.h"

using namespace VT;


MsgCatID VT::MsgCat_PluginExplorer;
MsgCatID VT::MsgCat_ErrorMsg;

IMessagePrinter::IMessagePrinter()
{
}

IMessagePrinter::~IMessagePrinter()
{
}

MsgCatID IMessagePrinter::RegisterMessageCategory(const std::string &categoryName)
{
	return RegisterMessageCategory_(categoryName);
}

void IMessagePrinter::PrintMessage(MsgCatID id,
	const std::string &text, bool append, bool makeCurrrentCategory)
{
	PrintMessage_(id, text, append, makeCurrrentCategory);
}
