#include "Vitals\IVitalsInterfaceManager.h"

using namespace VT;


namespace VT
{
	class VTInterfaceMngrAccessor
	{
	public:
		void SetVitalsInterfaceManager(IVitalsInterfaceManager *val)
		{
			vitalsInterfaceManager = val;
		}

		IPluginsManager* GetPluginsManager()
		{
			return vitalsInterfaceManager->GetPluginsManager();
		}

		ICallerManager* GetCallerManager()
		{
			return vitalsInterfaceManager->GetCallerManager();
		}

	private:
		IVitalsInterfaceManager *vitalsInterfaceManager;

	} vtInterfaceMngrAccessor;
}


void VT::SetVitalsInterfaceManager(IVitalsInterfaceManager *vitalsInterfaceManager)
{
	vtInterfaceMngrAccessor.SetVitalsInterfaceManager(vitalsInterfaceManager);
}

IPluginsManager* VT::GetPluginsManager()
{
	return vtInterfaceMngrAccessor.GetPluginsManager();
}

ICallerManager* VT::GetCallerManager()
{
	return vtInterfaceMngrAccessor.GetCallerManager();
}

IVitalsInterfaceManager::~IVitalsInterfaceManager()
{
}
