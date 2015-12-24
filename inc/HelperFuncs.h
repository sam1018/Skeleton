#pragma once

#include <functional>
#include <windows.h>

namespace HelperFuncs
{
	namespace Details
	{
		template <typename RetType>
		class FuncCaller
		{
			RetType val;
		public:
			FuncCaller(const std::function<RetType(void)> &f) { val = f(); }
			RetType GetRetVal() { return val; }
		};

		template<>
		class FuncCaller<void>
		{
		public:
			FuncCaller(const std::function<void(void)> &f) { f(); }
			void GetRetVal() {}
		};
	}

	// Requirements:
	// f must be callable
	// f must have an overload that takes args as its parameter
	template<typename FuncType, typename ...ArgTypes, typename RetType = std::result_of_t<FuncType&& (ArgTypes&&...)>>
	RetType SystemCallThrowing(const std::string &errMsg, FuncType &&f, ArgTypes&&... args)
	{
		SetLastError(0);

		auto ret = Details::FuncCaller<RetType>(
			[&]() { return std::invoke(std::forward<FuncType>(f), std::forward<ArgTypes>(args)...); } );

		if (auto err = GetLastError())
		{
			throw std::system_error(
				std::error_code(err, std::system_category()),
				errMsg);
		}

		return ret.GetRetVal();
	}
}
