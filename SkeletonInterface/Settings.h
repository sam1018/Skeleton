#pragma once

#include "SkeletonInterface.h"
#include <string>
#include <memory>
#include <boost\variant.hpp>

namespace Settings
{
	//////////////////////////////////////////////////////////////////////////
	// Template types in boost::variant and type checks in TypeCheck
	// function should contain same types
	// So that, if user uses wrong types, we get static assert fail
	// instead of the horrible compile errors that will come otherwise
	//////////////////////////////////////////////////////////////////////////
	using ValueType = boost::variant<int&, std::string&, bool&>;

	template <typename T>
	constexpr bool TypeCheck()
	{
		return std::is_same<T, int>() || std::is_same<T, std::string>() || std::is_same<T, bool>();
	}
	//////////////////////////////////////////////////////////////////////////

	class SKELETONINTERFACE_DECLSPEC AttribAccessor
	{
	public:
		AttribAccessor();
		~AttribAccessor();

		template <typename VT>
		void RegisterItem(VT &value, std::string path)
		{
			static_assert(TypeCheck<VT>(), "Static assertion failed: Unsupported item type.");
			InternalRegisterItem(ValueType(value), path);
		}

		void Load(std::string fileName);
		void Save(std::string fileName);

	private:
		void InternalRegisterItem(ValueType value, std::string path);

	private:
		struct ItemsImpl;

		// We can safely ignore C4251 in this case
#pragma warning( push )
#pragma warning( disable : 4251 )
		std::unique_ptr<ItemsImpl> m_pItemsImpl;
#pragma warning( pop ) 		
	};
}
