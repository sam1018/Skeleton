#include "Vitals\Caller.h"

using namespace VT;


struct Caller::CallerImpl
{
	FunctionType func;
	IPlugin *plugin;

	CallerImpl(FunctionType f, IPlugin *p) :
		func{ f },
		plugin{ p }
	{
	}

	std::unique_ptr<CallerImpl> Clone()
	{
		return std::make_unique<CallerImpl>(func, plugin);
	}
};

template <typename RetType>
class FunctionVisitor : public boost::static_visitor<RetType>
{
public:
	RetType operator()(std::function<RetType(void)> f)
	{
		f();
	}
};

Caller::Caller(FunctionType f, IPlugin *p) :
	callerImpl{ std::make_unique<CallerImpl>(f, p) }
{
}

Caller::~Caller()
{
}

Caller::Caller(const VT::Caller &right)
{
	callerImpl = right.callerImpl->Clone();
}

Caller::Caller(VT::Caller &&right)
{
	callerImpl = std::move(right.callerImpl);
}

Caller& Caller::operator=(Caller right)
{
	std::swap(*this, right);
	return *this;
}

void Caller::ExecuteCaller()
{
	FunctionVisitor<void> ob;
	boost::apply_visitor(ob, callerImpl->func);
}

IPlugin * VT::Caller::GetPlugin() const
{
	return callerImpl->plugin;
}
