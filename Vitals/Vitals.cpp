#include "Vitals.h"
#include "PluginsManager.h"
#include "CallerManager.h"
#include "MessagePrinter.h"
#include "Vitals\IVitalsInterfaceManager.h"


using namespace VT;


class VitalsInterfaceManager : public IVitalsInterfaceManager
{
public:
	VitalsInterfaceManager()
	{
	}

	~VitalsInterfaceManager()
	{
	}

private:
	virtual IPluginsManager* GetPluginsManager()
	{
		return &pluginsManager;
	}
	virtual ICallerManager* GetCallerManager()
	{
		return &CallerManager;
	}

	virtual IMessagePrinter* GetMessagePrinter()
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

	VITALS_DECLSPEC IVitalsInterfaceManager* GetInterfaceManager()
	{
		return &vitalsInterfaceManager;
	}

	VITALS_DECLSPEC void DestroyModule()
	{
	}
}
