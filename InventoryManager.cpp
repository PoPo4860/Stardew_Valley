#include "InventoryManager.h"


void InventoryManager::InventoryPush(ToolItemInfo* item ,ItemType* type)
{
	if (InventoryEmptyCheck() == false)
	{

	}
}

void InventoryManager::InventoryPush(ResourceItemInfo* item, ItemType* type)
{
	if (InventoryEmptyCheck() == false)
	{

	}
}

bool InventoryManager::InventoryEmptyCheck()
{
	for (int y = 0; y < 3; ++y)
	{
		for (int x = 0; x < 10; ++x)
		{
			if (inventory[y][x].first.itemType == ItemType::Empty)return true;
		}
	}
	return false;
}

void InventoryManager::Render(HDC hdc)
{

}

void InventoryManager::Uadate()
{
}
