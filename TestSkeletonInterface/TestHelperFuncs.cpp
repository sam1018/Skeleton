#include "stdafx.h"
#include "CppUnitTest.h"
#include "HelperFuncs.h"
#include <exception>
#include <vector>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace HelperFuncs;
using namespace std;

namespace TestSkeletonInterface
{
	void FuncGlobalRetVoid() {}
	void FuncGlobalRetVoidSetError() { SetLastError(1); }
	template<typename T>
	T FuncGlobalRetT(const T &ob) { return ob; }
	template<typename T>
	T FuncGlobalRetTSetError(const T &ob) { SetLastError(1); return ob; }

	TEST_CLASS(TestHelperFuncs)
	{
	public:
		TEST_METHOD(TestSystemCallThrowing)
		{
			// void return type is supported
			SystemCallThrowing("", FuncGlobalRetVoid);
			// We expect exception in this case
			Assert::ExpectException<std::system_error>([]() {SystemCallThrowing("", FuncGlobalRetVoidSetError); });
			auto retVal = "SomeRandomString";
			// Any other return type is also supported
			Assert::AreEqual(SystemCallThrowing("", FuncGlobalRetT<decltype(retVal)>, retVal), retVal);
			// We expect exception in this case
			Assert::ExpectException<std::system_error>([retVal]() {SystemCallThrowing("", FuncGlobalRetTSetError<decltype(retVal)>, retVal); });
		}
	};
}
