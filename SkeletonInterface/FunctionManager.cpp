#include "Plugin.h"
#include "FunctionManager.h"
#include <set>
#include <thread>
#include <mutex>

using namespace FctEx;

struct Function
{
	FunctionType func;
	Plugin *plugin;
};

using Functions = std::set<Function>;


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

bool operator<(const Function &f1, const Function &f2)
{
	AddressGetterForFunction ob;
	size_t f1_addr = boost::apply_visitor(ob, f1.func);
	size_t f2_addr = boost::apply_visitor(ob, f2.func);
	return f1_addr < f2_addr;
}

template <typename RetType>
class FunctionVisitor : public boost::static_visitor<RetType>
{
public:
	RetType operator()(std::function<RetType(void)> f)
	{
		f();
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

	void AddFunctions(const Functions &addFunctions)
	{
		std::lock_guard<std::mutex> lock(lockAddFuncs);
		addFuncs.insert(addFunctions.begin(), addFunctions.end());
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
				funcs.swap(addFuncs);
				addFuncs.clear();
				appendItems = false;
			}

			if (startNewCycle)
			{
				startNewCycle = false;

				readyForNewCycle = false;

				bool ret = StartCycle();

				for (auto& f : funcs)
				{
					FunctionVisitor<void> ob;
					boost::apply_visitor(ob, f.func);
				}

				funcs.clear();

				if (ret)
					EndCycle();

				readyForNewCycle = true;
			}
		}
	}

	void CallbackSetupThread(std::function<void(void)> f)
	{
		Init = f;
	}

	void CallbackStartCycle(std::function<bool(void)> f)
	{
		StartCycle = f;
	}

	void CallbackEndCycle(std::function<void(void)> f)
	{
		EndCycle = f;
	}

	void StartThread()
	{
		t = std::thread([this]() { Run(); });
	}

private:
	std::thread t;
	Functions funcs;
	Functions addFuncs;
	bool startNewCycle = false;
	bool keepGoing = true;
	bool appendItems = false;
	bool readyForNewCycle = true;
	std::mutex lockAddFuncs;

	std::function<void(void)> Init;
	std::function<bool(void)> StartCycle;
	std::function<void(void)> EndCycle;
};




struct FunctionManager::FunctionManagerImpl
{
	Functions oneTimeFunctions;
	Functions perFrameFunctions;

	Functions oneTimeFunctionsPending;
	Functions perFrameFunctionsPending;

	WorkerThread workerThread;
};

FunctionManager::FunctionManager() :
	functionManagerImpl{ std::make_unique<FunctionManagerImpl>() }
{
}

FunctionManager::~FunctionManager()
{
}

FunctionManager& FunctionManager::GetInstance()
{
	static FunctionManager theFunctionManager;
	return theFunctionManager;
}

bool FunctionManager::RequestNewCycle()
{
	if (!ReadyForNewCycle())
		return false;

	// Append pending operations

	if (functionManagerImpl->oneTimeFunctionsPending.size())
	{
		std::swap(functionManagerImpl->oneTimeFunctions, functionManagerImpl->oneTimeFunctionsPending);
		functionManagerImpl->oneTimeFunctionsPending.clear();
	}

	if (functionManagerImpl->perFrameFunctionsPending.size())
	{
		functionManagerImpl->perFrameFunctions.insert(functionManagerImpl->perFrameFunctionsPending.begin(), 
			functionManagerImpl->perFrameFunctionsPending.end());

		functionManagerImpl->perFrameFunctionsPending.clear();
	}

	functionManagerImpl->workerThread.AddFunctions(functionManagerImpl->oneTimeFunctions);
	functionManagerImpl->workerThread.AddFunctions(functionManagerImpl->perFrameFunctions);
	functionManagerImpl->workerThread.AppendItems();
	functionManagerImpl->workerThread.StartNewCycle();


	functionManagerImpl->oneTimeFunctions.clear();


	return true;
}

bool FunctionManager::ReadyForNewCycle()
{
	return functionManagerImpl->workerThread.IsReadyForNewCycle();
}

void FunctionManager::CallbackSetupThread(std::function<void(void)> f)
{
	functionManagerImpl->workerThread.CallbackSetupThread(f);
}

void FunctionManager::CallbackStartCycle(std::function<bool(void)> f)
{
	functionManagerImpl->workerThread.CallbackStartCycle(f);
}

void FunctionManager::CallbackEndCycle(std::function<void(void)> f)
{
	functionManagerImpl->workerThread.CallbackEndCycle(f);
}

void FunctionManager::StartThread()
{
	functionManagerImpl->workerThread.StartThread();
}

void FunctionManager::InternalRegisterFunction(FunctionType func, CallType callType, Plugin *plugin)
{
	if (callType == CallType::OneTime)
		functionManagerImpl->oneTimeFunctionsPending.insert(Function{ func, plugin });
	else if (callType == CallType::EveryTime)
		functionManagerImpl->perFrameFunctionsPending.insert(Function{ func, plugin });
}
