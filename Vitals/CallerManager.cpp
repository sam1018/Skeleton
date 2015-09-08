#include "Plugin.h"
#include "CallerManager.h"
#include "Vitals\IMessagePrinter.h"
#include "Vitals\IVitalsInterfaceManager.h"
#include <vector>
#include <mutex>
#include <thread>
#include <atomic>
#include <iostream>

using namespace VT;
using namespace std;


using Callers = vector<Caller>;


class AddressGetterForFunction : public boost::static_visitor<size_t>
{
public:
	template<typename T, typename... U>
	size_t operator()(function<T(U...)> f)
	{
		typedef T(fnType)(U...);
		fnType ** fnPointer = f.template target<fnType*>();
		return (size_t)*fnPointer;
	}
};


class WorkerThread
{
public:
	WorkerThread()
	{
	}

	~WorkerThread()
	{
		keepGoing = false;
		if (StartThreadCalled)
			t.join();
	}

	void CallbackSetupThread(function<void(void)> f)
	{
		CheckStartThreadCall();
		Init = f;
	}

	void CallbackStartCycle(function<bool(void)> f)
	{
		CheckStartThreadCall();
		StartCycle = f;
	}

	void CallbackEndCycle(function<void(void)> f)
	{
		CheckStartThreadCall();
		EndCycle = f;
	}

	void StartThread()
	{
		StartThreadCalled = true;

		IMessagePrinter *mp = GetMessagePrinter();
		MsgCatID id = mp->RegisterMessageCategory("Output");

		//outRedirHandler = mp->RedirectStream(cout, id);
		//errRedirHandler = mp->RedirectStream(cerr, id);


		t = thread([this]() { Run(); });
	}

	void AddCallers(const Callers &callers)
	{
		lock_guard<mutex> lock(lockAddFuncs);
		addCallers.insert(addCallers.end(), callers.begin(), callers.end());
	}

	void AppendItems()
	{
		appendItems = true;
	}

	void StartNewCycle()
	{
		startNewCycle = true;
	}

	bool IsReadyForNewCycle()
	{
		return readyForNewCycle;
	}

	void Run()
	{
		Init();

		while (keepGoing)
		{
			if (appendItems)
			{
				lock_guard<mutex> lock(lockAddFuncs);
				callers.swap(addCallers);
				addCallers.clear();
				appendItems = false;
			}

			if (startNewCycle)
			{
				startNewCycle = false;

				readyForNewCycle = false;

				bool ret = StartCycle();

				for_each(callers.begin(), callers.end(), 
					[](Caller &caller) { caller.ExecuteCaller(); });

				callers.clear();

				if (ret)
					EndCycle();

				readyForNewCycle = true;
			}
		}
	}

private:
	void CheckStartThreadCall()
	{
		if (StartThreadCalled)
			throw runtime_error("Error!!! This function cannot be called after call to StartThread()");
	}

private:
	thread t;

	// <Following variables need mutex guard>
	Callers addCallers;
	mutex lockAddFuncs;
	// </>

	// <Following variables need atomic>
	atomic<bool> startNewCycle = false; // GUI thread asks for a new cycle
	atomic<bool> keepGoing = true; // To keep thread loop running
	atomic<bool> appendItems = false; // Some new Callers need to be added for execution
	atomic<bool> readyForNewCycle = true; // To convey we are ready for new cycle
	//</>

	// <Following variables don't need atomic, as they won't be accessed within Run()>
	bool StartThreadCalled = false;
	//</>

	// <Following variables don't need atomic
	// As except for initialization, they are only used within Run()>
	Callers callers; 
	unique_ptr<IRedirHandler> outRedirHandler;
	unique_ptr<IRedirHandler> errRedirHandler;
	// </>

	// <Following variables don't need atomic, as we make sure, calling them after StartThread() calll is an error>
	function<void(void)> Init;
	function<bool(void)> StartCycle;
	function<void(void)> EndCycle;
	// </>
};




struct CallerManager::CallerManagerImpl
{
	Callers oneTimeCallersPending;
	Callers perFrameCallersPending;

	WorkerThread workerThread;
};

CallerManager::CallerManager() :
	callerManagerImpl{ make_unique<CallerManagerImpl>() }
{
}

CallerManager::~CallerManager()
{
}

void CallerManager::PluginUnloaded_(IPlugin *plugin)
{
	auto remPred = [plugin](const Caller &caller) { return caller.GetPlugin() == plugin; };

	remove_if(callerManagerImpl->oneTimeCallersPending.begin(),
		callerManagerImpl->oneTimeCallersPending.end(), remPred);

	remove_if(callerManagerImpl->perFrameCallersPending.begin(),
		callerManagerImpl->perFrameCallersPending.end(), remPred);
}

bool CallerManager::RequestNewCycle_()
{
	if (!ReadyForNewCycle())
		return false;

	callerManagerImpl->workerThread.AddCallers(move(callerManagerImpl->oneTimeCallersPending));
	callerManagerImpl->workerThread.AddCallers(callerManagerImpl->perFrameCallersPending);
	callerManagerImpl->workerThread.AppendItems();
	callerManagerImpl->workerThread.StartNewCycle();

	// To return the object to a known state, after move
	callerManagerImpl->oneTimeCallersPending.clear();


	return true;
}

bool CallerManager::ReadyForNewCycle_()
{
	return callerManagerImpl->workerThread.IsReadyForNewCycle();
}

void CallerManager::CallbackSetupThread_(function<void(void)> f)
{
	callerManagerImpl->workerThread.CallbackSetupThread(f);
}

void CallerManager::CallbackStartCycle_(function<bool(void)> f)
{
	callerManagerImpl->workerThread.CallbackStartCycle(f);
}

void CallerManager::CallbackEndCycle_(function<void(void)> f)
{
	callerManagerImpl->workerThread.CallbackEndCycle(f);
}

void CallerManager::StartThread_()
{
	callerManagerImpl->workerThread.StartThread();
}

void CallerManager::RegisterCaller_(Caller &&caller, CallType callType)
{
	if (callType == CallType::OneTime)
		callerManagerImpl->oneTimeCallersPending.push_back(move(caller));
	else if (callType == CallType::EveryTime)
		callerManagerImpl->perFrameCallersPending.push_back(move(caller));
}
