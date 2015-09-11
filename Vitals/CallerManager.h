#pragma once

#include "Vitals\ICallerManager.h"
#include <functional>
#include <memory>

class Plugin;


class CallerManager : public VT::ICallerManager
{
public:
	CallerManager();
	~CallerManager();

private:

	virtual void RegisterCaller_(VT::Caller &&caller, VT::CallType callType);

	// This plugin is unloaded
	// We need to remove all functions from this plugin
	virtual void PluginUnloaded_(VT::IPlugin *plugin);

	// Returns whether request accepted
	// Request will be accepted if ReadyForNewCycle() is true
	virtual bool RequestNewCycle_();
	virtual bool ReadyForNewCycle_();

	virtual void CallbackSetupThread_(std::function<void(void)> f);
	virtual void CallbackStartCycle_(std::function<bool(void)> f);
	virtual void CallbackEndCycle_(std::function<void(void)> f);

	virtual void StartThread_();

	virtual std::function<void(double)> CallbackPlay_();
	virtual std::function<void(void)> CallbackPause_();

	virtual void SetAchievedCPSCallback_(std::function<void(double)> AchievedCPSCallback);

	virtual void Init_();

private:
	struct CallerManagerImpl;
	std::unique_ptr<CallerManagerImpl> callerManagerImpl;
};
