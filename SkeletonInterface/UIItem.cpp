#include "UI/UIItem.h"
#include <vector>

using namespace UI;

class UIItems
{
	using Items = std::vector<UIItem*>;
public:
	static UIItems& GetInstance()
	{
		static UIItems theUIItems;
		return theUIItems;
	}

	void AddItem(std::string name, UIItem *item)
	{
		uiItems.push_back(item);
	}

	Items& GetItems()
	{
		return uiItems;
	}

private:
	UIItems() {}
	~UIItems() {}

private:
	Items uiItems;
};

UI::UIItem::UIItem()
{
	// Dummy register
	UIItems::GetInstance().AddItem("", this);
}

UIItem::~UIItem()
{
}

void UI::InitializeItems()
{
	for (auto &item : UIItems::GetInstance().GetItems())
		item->InitializeItem();
}

void UI::Cleanup()
{
	for (auto &item : UIItems::GetInstance().GetItems())
		item->Cleanup();
}
