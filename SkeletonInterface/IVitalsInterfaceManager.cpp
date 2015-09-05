#include "Vitals\IVitalsInterfaceManager.h"
#include <cassert>

using namespace VT;



#define ADD_PROP(RetType, FuncName) \
RetType FuncName() \
{ \
	assert(vitalsInterfaceManager != nullptr); \
	return vitalsInterfaceManager->FuncName(); \
}

namespace VT
{
	class VTInterfaceMngrAccessor
	{
	public:
		void SetVitalsInterfaceManager(IVitalsInterfaceManager *val)
		{
			vitalsInterfaceManager = val;
		}

		ADD_PROP(IPluginsManager*, GetPluginsManager)
		ADD_PROP(ICallerManager*, GetCallerManager)
		ADD_PROP(IMessagePrinter*, GetMessagePrinter)

	private:
		IVitalsInterfaceManager *vitalsInterfaceManager;

	} vtInterfaceMngrAccessor;
}


IVitalsInterfaceManager::~IVitalsInterfaceManager()
{
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

IMessagePrinter* VT::GetMessagePrinter()
{
	return vtInterfaceMngrAccessor.GetMessagePrinter();
}
