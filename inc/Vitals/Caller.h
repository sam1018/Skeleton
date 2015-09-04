#pragma once

#include "IPlugin.h"
#include"../SkeletonInterface.h"
#include <functional>
#include <boost\variant.hpp>



///////////////////////////////////////////////////////////////////////////////
///////////   Users will use CreateCaller function   //////////////////////////
//////   Check below on how to support a new function signature   /////////////
///////////////////////////////////////////////////////////////////////////////



namespace VT
{
	enum class CallType
	{
		OneTime,
		EveryTime
	};

	// Add new signature below to support new function signature type
	// Then update following places:
	// 1. FunctionType, add by separating with a comma
	// 2. TypeCheck, add new check through std::is_same
	// <signature list>
	using FuncSig1 = std::function<void(void)>;
	// </signature list>

	// <1. FunctionType>
	using FunctionType = boost::variant<FuncSig1>;
	// </1. FunctionType>

	// <2. TypeCheck>
	template<typename T>
	struct IsSupportedSignature
	{
		static const bool value = false;
	};

	template<>
	struct IsSupportedSignature<FuncSig1>
	{
		static const bool value = true;
	};
	// </2. TypeCheck>
	//////////////////////////////////////////////////////////////////////////




	class SKELETONINTERFACE_DECLSPEC Caller
	{
		template <typename FuncSig>
		friend Caller CreateCaller(FuncSig f, IPlugin *plugin);
	public:
		Caller(const VT::Caller &right);
		Caller(VT::Caller &&right);
		Caller& operator=(Caller right);
		~Caller();

		void ExecuteCaller();
		IPlugin* GetPlugin() const;
	private:
		Caller(FunctionType f, IPlugin *p);
	private:
		struct CallerImpl;
		// We can safely ignore C4251 in this case
#pragma warning( push )
#pragma warning( disable : 4251 )
		std::unique_ptr<CallerImpl> callerImpl;
#pragma warning( pop ) 		
	};

	// Create new CreateCaller function if you need to support function with different signature
	template <typename FuncSig>
	Caller CreateCaller(FuncSig f, IPlugin *plugin)
	{
		static_assert(IsSupportedSignature<FuncSig>::value, "Function signature not supported.");

		return Caller{ FunctionType{f}, plugin };
	}

	void ExecuteCaller(const Caller &caller);
}
