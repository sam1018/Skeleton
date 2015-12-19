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
using namespace chrono;


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
	using DurationTypeLLMicro = duration<long long, ratio<1, 1000000>>;
	using DurationTypeDS = duration<double>;

public:
	WorkerThread()
	{
	}

	~WorkerThread()
	{
		keepGoing = false;
		if (t.joinable())
			t.join();
	}

	void CallbackSetupThread(function<void(void)> f)
	{
		CheckStartThreadCall();
		CallFromYourThread = f;
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

		if (cmSettings.redirectErrStream || cmSettings.redirectOutStream)
		{
			IMessagePrinter *mp = GetMessagePrinter();
			MsgCatID id = mp->RegisterMessageCategory("Output");

			if (cmSettings.redirectOutStream)
				outRedirHandler = mp->RedirectStream(cout, id);

			if (cmSettings.redirectErrStream)
				errRedirHandler = mp->RedirectStream(cerr, id);
		}

		t = thread([this]() { Run(); });
	}

	void Init()
	{
		if (cmSettings.redirectErrStream || cmSettings.redirectOutStream)
		{
			IMessagePrinter *mp = GetMessagePrinter();
			MsgCatID id = mp->RegisterMessageCategory("Output");

			if (cmSettings.redirectOutStream)
				outRedirHandler = mp->RedirectStream(cout, id);

			if (cmSettings.redirectErrStream)
				errRedirHandler = mp->RedirectStream(cerr, id);
		}
	}

	void AddCallers(const Callers &c)
	{
		lock_guard<mutex> lock(lockAddFuncs);
		addCallers.insert(addCallers.end(), c.begin(), c.end());
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

	void Play(double cps_, const Callers &callers_)
	{
		cps = cps_;
		duration<double> temp{1 / cps};
		callInterval = DurationTypeLLMicro{ static_cast<long long>(temp.count() * 
			DurationTypeLLMicro::period::den) };

		callers = callers_;

		Pause();

		if (t.joinable())
			t.join();

		keepGoing = true;

		t = thread([this]() { Run(); });
	}

	void Pause()
	{
		keepGoing = false;
	}

	void SetAchievedCPSCallback(std::function<void(double)> AchievedCPSCallback_)
	{
		AchievedCPSCallback = AchievedCPSCallback_;
	}

private:
	void AchievedCPSCounter()
	{
		cpsCounter++;

		ck2_achievedCPSCnt = std::chrono::high_resolution_clock::now();

		auto diff = ck2_achievedCPSCnt - ck1_achievedCPSCnt;

		if (diff >= 1s)
		{
			if ((callInterval >= 1s && diff >= callInterval) ||
				(callInterval < 1s && diff > 1s))
			{
				DurationTypeDS duration = diff;
				AchievedCPSCallback(cpsCounter / duration.count());

				cpsCounter = 0;
				ck1_achievedCPSCnt = std::chrono::high_resolution_clock::now();
			}
		}
	}

	void Run()
	{
		CallFromYourThread();

		ck1_achievedCPSCnt = std::chrono::high_resolution_clock::now();

		auto startPoint = high_resolution_clock::now();
		int callCounter = 0;

		while (keepGoing)
		{
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

			AchievedCPSCounter();

			auto currentPoint = high_resolution_clock::now();
			callCounter++;
			auto curDuration = duration_cast<DurationTypeDS>(currentPoint - startPoint);
			auto reqDuration = DurationTypeDS{ callCounter * callInterval };
			auto diff = reqDuration - curDuration;

			if (diff.count() > 0)
			{
				while (diff > 500ms && keepGoing)
				{
					this_thread::sleep_for(500ms);
					diff -= 500ms;
				}
				if (diff > 0ms)
					this_thread::sleep_for(duration_cast<DurationTypeLLMicro>(diff));
			}
		}
	}

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
	CallerManagerSettings cmSettings;
	//</>

	// <Following variables don't need atomic
	// As except for initialization, they are only used within Run()>
	Callers callers; 
	unique_ptr<IRedirHandler> outRedirHandler;
	unique_ptr<IRedirHandler> errRedirHandler;
	// </>

	// <Following variables don't need atomic, as we make sure, calling them after StartThread() calll is an error>
	function<void(void)> CallFromYourThread;
	function<bool(void)> StartCycle;
	function<void(void)> EndCycle;
	// </>

	DurationTypeLLMicro callInterval;
	time_point<steady_clock> ck1_achievedCPSCnt;
	time_point<steady_clock> ck2_achievedCPSCnt;
	int cpsCounter = 0;
	std::function<void(double)> AchievedCPSCallback;
	double cps;
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

std::function<void(double)> CallerManager::CallbackPlay_()
{
	return [this](double cps) 
	{
		callerManagerImpl->workerThread.Play(cps, callerManagerImpl->perFrameCallersPending);
	};
}

std::function<void(void)> CallerManager::CallbackPause_()
{
	return [this]() { callerManagerImpl->workerThread.Pause(); };
}

void CallerManager::RegisterCaller_(Caller &&caller, CallType callType)
{
	if (callType == CallType::OneTime)
		callerManagerImpl->oneTimeCallersPending.push_back(move(caller));
	else if (callType == CallType::EveryTime)
		callerManagerImpl->perFrameCallersPending.push_back(move(caller));
}

void CallerManager::SetAchievedCPSCallback_(std::function<void(double)> AchievedCPSCallback)
{
	callerManagerImpl->workerThread.SetAchievedCPSCallback(AchievedCPSCallback);
}

void CallerManager::Init_()
{
	callerManagerImpl->workerThread.Init();
}
