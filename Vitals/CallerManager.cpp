#include "Plugin.h"
#include "CallerManager.h"
#include <vector>
#include <mutex>
#include <thread>
#include <atomic>

using namespace VT;


using Callers = std::vector<Caller>;


class AddressGetterForFunction : public boost::static_visitor<size_t>
{
public:
	template<typename T, typename... U>
	size_t operator()(std::function<T(U...)> f)
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
		t.join();
	}

	void CallbackSetupThread(std::function<void(void)> f)
	{
		CheckStartThreadCall();
		Init = f;
	}

	void CallbackStartCycle(std::function<bool(void)> f)
	{
		CheckStartThreadCall();
		StartCycle = f;
	}

	void CallbackEndCycle(std::function<void(void)> f)
	{
		CheckStartThreadCall();
		EndCycle = f;
	}

	void StartThread()
	{
		StartThreadCalled = true;
		t = std::thread([this]() { Run(); });
	}

	void AddCallers(const Callers &callers)
	{
		std::lock_guard<std::mutex> lock(lockAddFuncs);
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
				std::lock_guard<std::mutex> lock(lockAddFuncs);
				callers.swap(addCallers);
				addCallers.clear();
				appendItems = false;
			}

			if (startNewCycle)
			{
				startNewCycle = false;

				readyForNewCycle = false;

				bool ret = StartCycle();

				std::for_each(callers.begin(), callers.end(), 
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
			throw std::runtime_error("Error!!! This function cannot be called after call to StartThread()");
	}

private:
	std::thread t;

	// <Following variables need mutex guard>
	Callers addCallers;
	std::mutex lockAddFuncs;
	// </>

	// <Following variables need atomic>
	std::atomic<bool> startNewCycle = false; // GUI thread asks for a new cycle
	std::atomic<bool> keepGoing = true; // To keep thread loop running
	std::atomic<bool> appendItems = false; // Some new Callers need to be added for execution
	std::atomic<bool> readyForNewCycle = true; // To convey we are ready for new cycle
	//</>

	// <Following variables don't need atomic, as they won't be accessed within Run()>
	bool StartThreadCalled = false;
	//</>

	// <Following variables don't need atomic, as they are only used within Run()>
	Callers callers;
	// </>

	// <Following variables don't need atomic, as we make sure, calling them after StartThread() calll is an error>
	std::function<void(void)> Init;
	std::function<bool(void)> StartCycle;
	std::function<void(void)> EndCycle;
	// </>
};




struct CallerManager::CallerManagerImpl
{
	Callers oneTimeCallersPending;
	Callers perFrameCallersPending;

	WorkerThread workerThread;
};

CallerManager::CallerManager() :
	callerManagerImpl{ std::make_unique<CallerManagerImpl>() }
{
}

CallerManager::~CallerManager()
{
}

void CallerManager::PluginUnloaded_(IPlugin *plugin)
{
	auto remPred = [plugin](const Caller &caller) { return caller.GetPlugin() == plugin; };

	std::remove_if(callerManagerImpl->oneTimeCallersPending.begin(),
		callerManagerImpl->oneTimeCallersPending.end(), remPred);

	std::remove_if(callerManagerImpl->perFrameCallersPending.begin(),
		callerManagerImpl->perFrameCallersPending.end(), remPred);
}

bool CallerManager::RequestNewCycle_()
{
	if (!ReadyForNewCycle())
		return false;

	callerManagerImpl->workerThread.AddCallers(std::move(callerManagerImpl->oneTimeCallersPending));
	callerManagerImpl->workerThread.AddCallers(callerManagerImpl->perFrameCallersPending);
	callerManagerImpl->workerThread.AppendItems();
	callerManagerImpl->workerThread.StartNewCycle();

	// To return the object to a known state, after std::move
	callerManagerImpl->oneTimeCallersPending.clear();


	return true;
}

bool CallerManager::ReadyForNewCycle_()
{
	return callerManagerImpl->workerThread.IsReadyForNewCycle();
}

void CallerManager::CallbackSetupThread_(std::function<void(void)> f)
{
	callerManagerImpl->workerThread.CallbackSetupThread(f);
}

void CallerManager::CallbackStartCycle_(std::function<bool(void)> f)
{
	callerManagerImpl->workerThread.CallbackStartCycle(f);
}

void CallerManager::CallbackEndCycle_(std::function<void(void)> f)
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
		callerManagerImpl->oneTimeCallersPending.push_back(std::move(caller));
	else if (callType == CallType::EveryTime)
		callerManagerImpl->perFrameCallersPending.push_back(std::move(caller));
}
