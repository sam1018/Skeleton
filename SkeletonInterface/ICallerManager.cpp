#include "Vitals\ICallerManager.h"

using namespace VT;

void ICallerManager::CallbackSetupThread(std::function<void(void)> f)
{
	CallbackSetupThread_(f);
}

void ICallerManager::CallbackStartCycle(std::function<bool(void)> f)
{
	CallbackStartCycle_(f);
}

void ICallerManager::CallbackEndCycle(std::function<void(void)> f)
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
	RegisterCaller_(std::move(caller), callType);
}

void ICallerManager::PluginUnloaded(IPlugin *plugin)
{
	PluginUnloaded_(plugin);
}
