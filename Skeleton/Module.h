#include <codecvt>
#include <iostream>
#include <system_error>
#include <windows.h>
#include <boost/type_index.hpp>




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

void ThrowSystemError(const std::string &errMsg)
{
	auto ec = std::error_code(GetLastError(), std::system_category());
	throw std::system_error(ec, errMsg);
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
		hinstLib = LoadLibrary(s2ws(moduleName).c_str());

		if (!hinstLib)
			ThrowSystemError("Failed to load module: \"" + moduleName + "\".");
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
		if (!FreeLibrary(hinstLib))
			ThrowSystemError("Failed to unload module: \"" + moduleName + "\".");
	}

	template <typename FuncType>
	FuncType GetFunctionAddress(const std::string &funcName) const
	{
		FuncType func = reinterpret_cast<FuncType>(GetProcAddress(hinstLib, funcName.c_str()));
		if (!func)
			ThrowSystemError("Failed to load funcion: \"" + funcName +
				"\", in Module: \"" + moduleName + "\".");

		return func;
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
	Module(const std::string &name, int argc, char** argv) :
		moduleImpl{ name, argc, argv }
	{}

	InterfaceManagerType GetInterfaceManager() const;

private:
	ModuleImpl<InterfaceManagerType> moduleImpl;
};

template <typename InterfaceManagerType>
InterfaceManagerType Module<InterfaceManagerType>::GetInterfaceManager() const
{
	return moduleImpl.GetInterfaceManager();
}
