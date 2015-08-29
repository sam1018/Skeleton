#include "Settings.h"
#include <vector>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

using namespace Settings;

namespace pt = boost::property_tree;

struct Item
{
	ValueType value;
	std::string path;
};

using Items = std::vector<Item>;

struct AttribAccessor::ItemsImpl
{
	Items items;
};

class ValueAccessor : public boost::static_visitor<>
{
public:
	enum class AccessType
	{
		STORE_IN_TREE,
		LOAD_FROM_TREE
	};

	ValueAccessor(pt::ptree &tree, std::string &path, AccessType accessType) :
		tree{ tree },
		path{ path },
		accessType{ accessType }
	{}

	template <typename T>
	void operator()(T &item)
	{
		if (accessType == AccessType::STORE_IN_TREE)
			tree.put(path, item);
		else
			item = tree.get<T>(path);
	}

private:
	pt::ptree &tree;
	const std::string &path;
	AccessType accessType;
};

void AccessTree(std::string fileName, Items &items, ValueAccessor::AccessType accessType)
{
	pt::ptree tree;

	if (accessType == ValueAccessor::AccessType::LOAD_FROM_TREE)
		pt::read_xml(fileName, tree);

	for (auto &item : items)
	{
		ValueAccessor f(tree, item.path, accessType);
		boost::apply_visitor(f, item.value);
	}

	if (accessType == ValueAccessor::AccessType::STORE_IN_TREE)
		pt::write_xml(fileName, tree);
}


///////////////////////////////////////////////////////////////////////////////
/////////////          AttribAccessor Definition                   ////////////
///////////////////////////////////////////////////////////////////////////////


AttribAccessor::AttribAccessor() :
	itemsImpl{ std::make_unique<ItemsImpl>() }
{
}

AttribAccessor::~AttribAccessor()
{
}

void AttribAccessor::Load(std::string fileName)
{
	AccessTree(fileName, itemsImpl->items, ValueAccessor::AccessType::LOAD_FROM_TREE);
}

void AttribAccessor::Save(std::string fileName)
{
	AccessTree(fileName, itemsImpl->items, ValueAccessor::AccessType::STORE_IN_TREE);
}

void AttribAccessor::InternalRegisterItem(ValueType value, std::string path)
{
	itemsImpl->items.push_back(Item{ value, path });
}
