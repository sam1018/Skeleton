#include "Settings.h"
#include <vector>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

using namespace Settings;

namespace pt = boost::property_tree;

struct Item
{
	ValueType mValue;
	std::string mPath;
};

using Items = std::vector <Item>;

struct AttribAccessor::ItemsImpl
{
	Items mItems;
};

class ValueAccessor : public boost::static_visitor<>
{
public:
	enum class AccessType
	{
		STORE_IN_TREE,
		LOAD_FROM_TREE
	};

	ValueAccessor(pt::ptree &pTree, std::string &path, AccessType accessType) :
		m_pTree{ pTree },
		mPath{ path },
		mAccessType{ accessType }
	{}

	template <typename T>
	void operator()(T &item)
	{
		if (mAccessType == AccessType::STORE_IN_TREE)
			m_pTree.put(mPath, item);
		else
			item = m_pTree.get<T>(mPath);
	}

private:
	pt::ptree &m_pTree;
	const std::string &mPath;
	AccessType mAccessType;
};

void AccessTree(std::string fileName, Items &items, ValueAccessor::AccessType accessType)
{
	pt::ptree tree;

	if (accessType == ValueAccessor::AccessType::LOAD_FROM_TREE)
		pt::read_xml(fileName, tree);

	for (auto &item : items)
	{
		ValueAccessor f(tree, item.mPath, accessType);
		boost::apply_visitor(f, item.mValue);
	}

	if (accessType == ValueAccessor::AccessType::STORE_IN_TREE)
		pt::write_xml(fileName, tree);
}

AttribAccessor::AttribAccessor() :
	m_pItemsImpl{ std::make_unique<ItemsImpl>() }
{
}

AttribAccessor::~AttribAccessor()
{
}

void AttribAccessor::Load(std::string fileName)
{
	AccessTree(fileName, m_pItemsImpl->mItems, ValueAccessor::AccessType::LOAD_FROM_TREE);
}

void AttribAccessor::Save(std::string fileName)
{
	AccessTree(fileName, m_pItemsImpl->mItems, ValueAccessor::AccessType::STORE_IN_TREE);
}

void AttribAccessor::InternalRegisterItem(ValueType value, std::string path)
{
	m_pItemsImpl->mItems.push_back(Item{ value, path });
}
