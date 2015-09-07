#include "Vitals\Caller.h"

using namespace VT;
using namespace std;


struct Caller::CallerImpl
{
	FunctionType func;
	IPlugin *plugin;

	CallerImpl(FunctionType f, IPlugin *p) :
		func{ f },
		plugin{ p }
	{
	}

	unique_ptr<CallerImpl> Clone()
	{
		return make_unique<CallerImpl>(func, plugin);
	}
};

template <typename RetType>
class FunctionVisitor : public boost::static_visitor<RetType>
{
public:
	RetType operator()(function<RetType(void)> f)
	{
		f();
	}
};

Caller::Caller(FunctionType f, IPlugin *p) :
	callerImpl{ make_unique<CallerImpl>(f, p) }
{
}

Caller::~Caller()
{
}

Caller::Caller(const Caller &right)
{
	callerImpl = right.callerImpl->Clone();
}

Caller::Caller(Caller &&right)
{
	callerImpl = move(right.callerImpl);
}

Caller& Caller::operator=(Caller right)
{
	swap(*this, right);
	return *this;
}

void Caller::ExecuteCaller()
{
	FunctionVisitor<void> ob;
	boost::apply_visitor(ob, callerImpl->func);
}

IPlugin * Caller::GetPlugin() const
{
	return callerImpl->plugin;
}
