#pragma once

#include"Vitals\IMessagePrinter.h"
#include <memory>

class MessagePrinter : public VT::IMessagePrinter
{
public:
	MessagePrinter();
	virtual ~MessagePrinter();

private:
	virtual VT::MsgCatID RegisterMessageCategory_(const std::string &categoryName);
	virtual void PrintMessage_(VT::MsgCatID id,
		const std::string &text, bool append, bool makeCurrrentCategory);

private:
	class MessagePrinterImpl;
	std::unique_ptr<MessagePrinterImpl> messagePrinterImpl;
};
