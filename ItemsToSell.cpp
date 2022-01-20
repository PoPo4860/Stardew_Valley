#pragma warning(disable : 4996)
#include "ItemsToSell.h"
#include "CommonFunction.h"
#include "Image.h"


void ItemsToSell::BuyItem()
{
	int shopPurchaseNum = shopManager->GetShopSoldNum();
	if (shopPurchaseNum != -1)
	{
		int itemCode = shopManager->blackSmith.salesList[shopManager->salesListStartNum + shopPurchaseNum];
		if (itemCode == BAG)
		{
			if (GAMEDATA_MANAGER->GetPlayerMoney() >= BAG_BUY_MONEY)
			{
				if (INVEN_MANAGER->ChangeCloseStateToOpen())
				{
					GAMEDATA_MANAGER->AddPlayerMoney(-(BAG_BUY_MONEY));
				}
			}
		}
		else
		{
			const ResourceItemInfo* item = ITEM_MANAGER->GetResourceItem(itemCode);
			if (GAMEDATA_MANAGER->GetPlayerMoney() >= item->gold)
			{
				GAMEDATA_MANAGER->AddPlayerMoney(-(item->gold));
				INVEN_MANAGER->PushInventory(itemCode, 1);
			}
		}
	}
}

void ItemsToSell::SellItem()
{
	POINT inventory = shopManager->GetInventoryNum();
	if (inventory.x != -1 && inventory.y != 1)
	{
		int itemCode = INVEN_MANAGER->GetInventoryInfo(inventory.x, inventory.y)->itemCode;
		if (RESOURCE_ITEM(itemCode))
		{
			int sales = ITEM_MANAGER->GetResourceItem(itemCode)->gold;
			int itemNum = INVEN_MANAGER->GetInventoryInfo(inventory.x, inventory.y)->itemNum;
			int totalSales = sales * itemNum;
			INVEN_MANAGER->GetInventoryInfo(inventory.x, inventory.y)->Clear();
			GAMEDATA_MANAGER->AddPlayerMoney(totalSales);
		}
	}
}

void ItemsToSell::Init()
{
	salesListBag = ImageManager::GetSingleton()->FindImage("Image/Shop/Shop_Sale_Bag.bmp",16,16,1,1);
}

void ItemsToSell::RenderSaleslist(HDC hdc)
{
	for (int i = 0; i < 4; ++i)
	{
		if (BAG == i + shopManager->salesListStartNum)
		{
			// �Ǹ� ������ ���
			salesListBag->Render(hdc, 138, 49 + (26 * i), 0, 0);

			// ������ �̸� ���
			char num_char[256];
			string bagName = "����";
			strcpy(num_char, bagName.c_str());
			PrintText(hdc, num_char, 150, 41 + (26.5f * i), 16);
			// ������ ���� ���
			int money = BAG_BUY_MONEY;
			for (int j = 0; money > 0; ++j)
			{
				int number = (int)(money % 10);
				money = (int)(money / 10);
				char num_char[256];
				sprintf_s(num_char, "%d", number);
				PrintText(hdc, num_char, 350 - (j * 10), 41 + (27 * i), 13);
			}
		}
		else
		{
			// �Ǹ� ������ ���
			ITEM_MANAGER->ItemRender(hdc, shopManager->blackSmith.salesList[i + shopManager->salesListStartNum], 138, 49 + (26 * i));

			// ������ �̸� ���
			const ResourceItemInfo* item = ITEM_MANAGER->GetResourceItem(shopManager->blackSmith.salesList[i + shopManager->salesListStartNum]);
			char num_char[256];
			strcpy(num_char, item->name.c_str());
			PrintText(hdc, num_char, 150, 41 + (26.5f * i), 16);


			// ������ ���� ���
			int money = item->gold;
			for (int j = 0; money > 0; ++j)
			{
				int number = (int)(money % 10);
				money = (int)(money / 10);
				char num_char[256];
				sprintf_s(num_char, "%d", number);
				PrintText(hdc, num_char, 350 - (j * 10), 41 + (27 * i), 13);
			}
		}

		// ���� ���
		shopManager->coinImage->Render(hdc, 365, 43 + (26 * i));
	}
}
