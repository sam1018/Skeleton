#pragma once

#include "Caller.h"
#include "../Settings.h"
#include "../Routines.h"
#include"../SkeletonInterface.h"
#include <functional>

namespace VT
{
	struct CallerManagerSettings
	{
		Settings::AttribAccessor accessor;
		bool redirectOutStream;
		bool redirectErrStream;

		CallerManagerSettings()
		{
			accessor.RegisterItem(redirectOutStream, "SkeletonSettings.CallerManager.RedirectOutStream");
			accessor.RegisterItem(redirectErrStream, "SkeletonSettings.CallerManager.RedirectErrStream");

			accessor.Load(Routines::GlobalSettingsFilePath());
		}
	};



	class SKELETONINTERFACE_DECLSPEC ICallerManager
	{
	public:
		void CallbackSetupThread(std::function<void(void)> f);
		void CallbackStartCycle(std::function<bool(void)> f);
		void CallbackEndCycle(std::function<void(void)> f);
		void StartThread();
		bool ReadyForNewCycle();
		bool RequestNewCycle();
		void RegisterCaller(Caller &&caller, CallType callType);
		void PluginUnloaded(IPlugin *plugin);

	private:
		virtual void CallbackSetupThread_(std::function<void(void)> f) = 0;
		virtual void CallbackStartCycle_(std::function<bool(void)> f) = 0;
		virtual void CallbackEndCycle_(std::function<void(void)> f) = 0;
		virtual void StartThread_() = 0;
		virtual bool ReadyForNewCycle_() = 0;
		virtual bool RequestNewCycle_() = 0;
		virtual void RegisterCaller_(Caller &&caller, CallType callType) = 0;
		virtual void PluginUnloaded_(IPlugin *plugin) = 0;
	};
}
