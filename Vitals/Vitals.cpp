#include "Vitals.h"
#include "PluginsManager.h"
#include "CallerManager.h"
#include "MessagePrinter.h"
#include "Vitals\IVitalsInterfaceManager.h"

class VitalsInterfaceManager : public VT::IVitalsInterfaceManager
{
public:
	VitalsInterfaceManager()
	{
	}

	~VitalsInterfaceManager()
	{
	}

private:
	virtual VT::IPluginsManager* GetPluginsManager()
	{
		return &pluginsManager;
	}
	virtual VT::ICallerManager* GetCallerManager()
	{
		return &CallerManager;
	}

	virtual VT::IMessagePrinter* GetMessagePrinter()
	{
		return &messagePrinter;
	}

private:
	CallerManager CallerManager;
	PluginsManager pluginsManager;
	MessagePrinter messagePrinter;

} vitalsInterfaceManager;

extern "C"
{
	VITALS_DECLSPEC void InitializeModule(int argc, char** argv)
	{
	}

	VITALS_DECLSPEC VT::IVitalsInterfaceManager* GetInterfaceManager()
	{
		return &vitalsInterfaceManager;
	}

	VITALS_DECLSPEC void DestroyModule()
	{
	}
}
