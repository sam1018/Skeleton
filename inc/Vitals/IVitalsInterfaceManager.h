#pragma once

#include"../SkeletonInterface.h"

namespace VT
{
	class IPluginsManager;
	class ICallerManager;
	class IMessagePrinter;

	class SKELETONINTERFACE_DECLSPEC IVitalsInterfaceManager
	{
		friend class VTInterfaceMngrAccessor;

	public:
		virtual ~IVitalsInterfaceManager() = 0;

	private:
		virtual IPluginsManager* GetPluginsManager() = 0;
		virtual ICallerManager* GetCallerManager() = 0;
		virtual IMessagePrinter* GetMessagePrinter() = 0;
	};

	SKELETONINTERFACE_DECLSPEC void SetVitalsInterfaceManager(IVitalsInterfaceManager*);

	// Clients will use the following APIs to get Vitals interfaces
	SKELETONINTERFACE_DECLSPEC IPluginsManager* GetPluginsManager();
	SKELETONINTERFACE_DECLSPEC ICallerManager* GetCallerManager();
	SKELETONINTERFACE_DECLSPEC IMessagePrinter* GetMessagePrinter();
}
