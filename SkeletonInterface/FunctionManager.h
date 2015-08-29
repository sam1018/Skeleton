#pragma once

#include <functional>
#include <memory>
#include <boost\variant.hpp>

class Plugin;


namespace FctEx
{
	enum class CallType
	{
		OneTime,
		EveryTime
	};

	//////////////////////////////////////////////////////////////////////////
	// Template types in boost::variant and type checks in TypeCheck
	// function should contain same types
	// So that, if user uses wrong types, we get static assert fail
	// instead of the horrible compile errors that will come otherwise
	//////////////////////////////////////////////////////////////////////////
	using FunctionType = boost::variant<std::function<void(void)>>;

	template <typename T>
	constexpr bool TypeCheck()
	{
		return std::is_same<T, std::function<void(void)>>();
	}
	//////////////////////////////////////////////////////////////////////////

	class FunctionManager
	{
	private:
		FunctionManager();
		~FunctionManager();

	public:
		static FunctionManager& GetInstance();

		// Will be executed in next call cycle
		// Use CallType::OneTime if you want it to be called just once
		// Use CallType::EveryTime if you want it to be called in every call cycle
		template <typename FT>
		void RegisterFunction(FT func, CallType callType, Plugin *plugin)
		{
			static_assert(TypeCheck<FT>(), "Static assertion failed: Unsupported item type.");
			InternalRegisterFunction(FunctionType(func), callType, plugin);
		}

		// This plugin is unloaded
		// We need to remove all functions from this plugin
		void PluginUnloaded(Plugin *plugin) {}

		// Returns whether request accepted
		// Request will be accepted if ReadyForNewCycle() is true
		bool RequestNewCycle();
		bool ReadyForNewCycle();

		void CallbackSetupThread(std::function<void(void)> f);
		void CallbackStartCycle(std::function<bool(void)> f);
		void CallbackEndCycle(std::function<void(void)> f);

		void StartThread();

	private:
		void InternalRegisterFunction(FunctionType func, CallType callType, Plugin *plugin);

	private:
		struct FunctionManagerImpl;
		std::unique_ptr<FunctionManagerImpl> functionManagerImpl;
	};
}
