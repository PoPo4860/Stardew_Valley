#pragma once
#include "Config.h"
#include "ItemCode.h"
#include "InventoryItem.h"
class InventoryManager : public Singleton<InventoryManager>
{
private:
	pair<InventoryItem, int> inventory[3][10];
protected:

public:
	void InventoryPush(ToolItemInfo* item, ItemType* type);
	void InventoryPush(ResourceItemInfo* item, ItemType* type);
	bool InventoryEmptyCheck();
	void Render(HDC hdc);
	void Uadate();
};

