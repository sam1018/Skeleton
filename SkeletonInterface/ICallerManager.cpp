#include "Vitals\ICallerManager.h"

using namespace VT;
using namespace std;

void ICallerManager::CallbackSetupThread(function<void(void)> f)
{
	CallbackSetupThread_(f);
}

void ICallerManager::CallbackStartCycle(function<bool(void)> f)
{
	CallbackStartCycle_(f);
}

void ICallerManager::CallbackEndCycle(function<void(void)> f)
{
	CallbackEndCycle_(f);
}

void ICallerManager::StartThread()
{
	StartThread_();
}

bool ICallerManager::ReadyForNewCycle()
{
	return ReadyForNewCycle_();
}

bool ICallerManager::RequestNewCycle()
{
	return RequestNewCycle_();
}

void ICallerManager::RegisterCaller(Caller &&caller, CallType callType)
{
	RegisterCaller_(move(caller), callType);
}

void ICallerManager::PluginUnloaded(IPlugin *plugin)
{
	PluginUnloaded_(plugin);
}
