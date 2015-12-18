#include <codecvt>
#include <iostream>
#include <functional>
#include <system_error>
#include <windows.h>
#include <boost/type_index.hpp>


// Requirements:
// f must be callable
// f must have an overload that takes arg as its parameter
// f must return a value other than void
template
<
	typename Func, 
	typename ...Args, 
	typename RetType = std::result_of_t<Func(Args...)>
>
RetType SystemCallThrowing(const std::string &errMsg, const Func &f, Args ...args)
{
	SetLastError(0);

	auto ret = f(std::forward<Args>(args)...);

	if (auto err = GetLastError())
	{
		throw std::system_error(
			std::error_code(err, std::system_category()),
			errMsg);
	}

	return ret;
}


///////////////////////////////////////////////////////////////////////////////
/////////////    Users will only use the Module class    //////////////////////
//////////// And can ignore the rest of the code in this file  /////////
///////////////////////////////////////////////////////////////////////////////




std::wstring s2ws(const std::string &str)
{
	typedef std::codecvt_utf8<wchar_t> convert_typeX;
	std::wstring_convert<convert_typeX, wchar_t> converterX;

	return converterX.from_bytes(str);
}

template <typename InterfaceManagerType>
class ModuleImpl
{
public:
	ModuleImpl(const std::string &name, int argc, char** argv) :
		moduleName{ name }
	{
		try
		{
			LoadModule();
			InitializeModule(argc, argv);
			LoadInterfaceManager();
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << errMsg;
			exit(1);
		}
	}

	~ModuleImpl()
	{
		try
		{
			DestroyModule();
			UnloadModule();
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << errMsg;
			exit(1);
		}
	}

	InterfaceManagerType GetInterfaceManager() const
	{
		return interfaceManager;
	}

private:
	void LoadModule()
	{
		auto func = [](auto s) { return LoadLibrary(s); };
		auto msg = "Failed to load module: \""s + moduleName + "\"."s;
		hinstLib = SystemCallThrowing(msg, func, s2ws(moduleName).c_str());
	}

	void InitializeModule(int argc, char** argv) const
	{
		using FuncType = void(*)(int, char**);
		FuncType InitFunc = GetFunctionAddress<void(*)(int, char**)>("InitializeModule");
		InitFunc(argc, argv);
	}

	void LoadInterfaceManager()
	{
		using FuncType = InterfaceManagerType(*)(void);
		FuncType GetInterfaceManagerFunc = GetFunctionAddress<FuncType>("GetInterfaceManager");
		interfaceManager = GetInterfaceManagerFunc();
		if (!interfaceManager)
			throw std::runtime_error("Failed to retrieve " +
				boost::typeindex::type_id_with_cvr<InterfaceManagerType>().pretty_name() +
				" for module: \"" + moduleName + "\".");
	}

	void DestroyModule() const
	{
		using FuncType = void(*)(void);
		FuncType DestroyModuleFunc = GetFunctionAddress<FuncType>("DestroyModule");
		DestroyModuleFunc();
	}

	void UnloadModule() const
	{
		auto func = [](auto hinstLib) { return FreeLibrary(hinstLib); };
		auto msg = "Failed to unload module: \""s + moduleName + "\"."s;
		SystemCallThrowing(msg, func, hinstLib);
	}

	template <typename FuncType>
	FuncType GetFunctionAddress(const std::string &funcName) const
	{
		auto func = [](auto hinstLib, auto funcName) { return reinterpret_cast<FuncType>(GetProcAddress(hinstLib, funcName)); };
		auto msg = "Failed to load funcion: \""s + funcName +
			"\", in Module: \""s + moduleName + "\"."s;
		return SystemCallThrowing(msg, func, hinstLib, funcName.c_str());
	}

private:
	const std::string moduleName;
	HINSTANCE hinstLib;
	const std::string errMsg{ "\nIrrecoverable error!!! Exiting Application!!!\n" };
	InterfaceManagerType interfaceManager;
};




///////////////////////////////////////////////////////////////////////////////
//////////////              Module Class     //////////////////////////////////
///////////// User should use the following class    //////////////////////////
///////////////////////////////////////////////////////////////////////////////

template <typename InterfaceManagerType>
class Module
{
public:
	void Initialize(const std::string &name, int argc, char** argv);
	InterfaceManagerType GetInterfaceManager() const;

private:
	using ImplType = ModuleImpl<InterfaceManagerType>;
	std::unique_ptr<ImplType> moduleImpl;
};

template <typename InterfaceManagerType>
void Module<InterfaceManagerType>::Initialize(const std::string &name, int argc, char** argv)
{
	moduleImpl = std::make_unique<ImplType>(name, argc, argv);
}

template <typename InterfaceManagerType>
InterfaceManagerType Module<InterfaceManagerType>::GetInterfaceManager() const
{
	return moduleImpl->GetInterfaceManager();
}
