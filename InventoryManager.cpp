#include "InventoryManager.h"
#include "CommonFunction.h"
#include "Image.h"

#define SPACE_X 11
#define SPACE_Y 10

pair<bool, POINT> InventoryManager::GetInventoryNum(POINT mouse)
{
	bool check = false;
	POINT num{ -1,-1 };
	if (PtInRect(&(inventoryMain.rect), mouse))
	{	// �κ��丮 ���ο����� ���
		mouse.x -= inventoryMain.correctPos.x;
		mouse.y -= inventoryMain.correctPos.y;
		if (SPACE_X <= mouse.x && mouse.x <= SPACE_X + (TILE_SIZE * INVEN_SIZE_X))
			num.x = (LONG)(mouse.x - SPACE_X) / 16;
		if (SPACE_Y <= mouse.y && mouse.y <= SPACE_Y + TILE_SIZE)
			num.y = 0;
		else if (SPACE_Y + TILE_SIZE + 4 <= mouse.y && mouse.y <= SPACE_Y + (TILE_SIZE * 2) + 4)
			num.y = 1;
		else if (SPACE_Y + (TILE_SIZE * 2) + 5 <= mouse.y && mouse.y <= SPACE_Y + (TILE_SIZE * 3) + 5)
			num.y = 2;
		check = true;
	}
	return pair<bool, POINT>(check, num);
}
InventoryManager::InventoryManager()
	:inventory{}, inventoryMain{}, inventoryMenu{}, mouseClick{ -1,-1 }, activeCheck{ false }
{Init(); }

void InventoryManager::InventoryPush(ToolItemInfo* item ,ItemType* type, int itemCode, int itemNum)
{
	itemNum = InventoryAdd(itemCode, itemNum);
	if (itemNum > 0)
	{
		POINT retult = InventoryEmptyAdd(type, itemCode, itemNum);
		inventory[retult.y][retult.x].first.SetToolItemInfo(*item);
	}
}

void InventoryManager::InventoryPush(ResourceItemInfo* item, ItemType* type, int itemCode, int itemNum)
{
	itemNum = InventoryAdd(itemCode , itemNum);
	if (itemNum > 0)
	{
		POINT retult = InventoryEmptyAdd(type, itemCode, itemNum);
		inventory[retult.y][retult.x].first.SetResourceItemInfo(*item);
	}
}

int InventoryManager::InventoryAdd(int itemCode, int itemNum)
{
	for (int y = 0; y < INVEN_SIZE_Y; ++y)
	{
		for (int x = 0; x < INVEN_SIZE_X; ++x)
		{
			if (inventory[y][x].first.GetItemCode() == itemCode &&
				inventory[y][x].second < 64)
			{
				inventory[y][x].second += itemNum;
				if (inventory[y][x].second >= 64)
				{
					itemNum = inventory[y][x].second - 64;
					inventory[y][x].second -= itemNum;
				}
				else
					return 0;
			}	// ���� ������ �������� �κ��丮�� �ְ�, �ִ밹������ ���ٸ� �����߰�
		}
	}
	return itemNum;
}

POINT InventoryManager::InventoryEmptyAdd(ItemType* type, int itemCode, int itemNum)
{	// ����ִ� ���� �������� �߰��ϰ�, �� ��ġ ��ȯ
	POINT result;
	result.x = 0;
	result.y = 0;
	for (int y = 0; y < INVEN_SIZE_Y; ++y)
	{
		for (int x = 0; x < INVEN_SIZE_X; ++x)
		{
			if (inventory[y][x].first.GetItemType() == ItemType::Empty)
			{
				inventory[y][x].first.SetItemCode(itemCode);
				inventory[y][x].first.SetItemType(*type);
				inventory[y][x].second = itemNum;
				result.x = x;
				result.y = y;
				return result;
			}
		}
	}	
	return result;
}

bool InventoryManager::InventoryEmptyCheck()
{
	for (int y = 0; y < INVEN_SIZE_Y; ++y)
	{
		for (int x = 0; x < INVEN_SIZE_X; ++x)
		{
			if (inventory[y][x].first.GetItemType() == ItemType::Empty) return true;
		}
	}
	return false;
}

void InventoryManager::Init()
{
	inventoryMain.img = ImageManager::GetSingleton()->FindImage("Image/Inventory/Inventory_Main.bmp", 213, 146, 1, 1);
	inventoryMain.pos.x = (WIN_SIZE_X / 2); inventoryMain.pos.y = (WIN_SIZE_Y / 2);
	inventoryMain.correctPos.x = inventoryMain.pos.x - (inventoryMain.img->GetFrameWidth() / 2);
	inventoryMain.correctPos.y = inventoryMain.pos.y - (inventoryMain.img->GetFrameHeight() / 2);
	SetRect(&inventoryMain.rect,inventoryMain.pos, 
		(inventoryMain.img->GetFrameWidth()), (inventoryMain.img->GetFrameHeight()));

	inventoryMenu.img = ImageManager::GetSingleton()->FindImage("Image/Inventory/Inventory_Menu.bmp", 128, 16, 8, 1);
	inventoryMenu.pos.x = (WIN_SIZE_X / 2); inventoryMenu.pos.y = (WIN_SIZE_Y / 2);
	inventoryMenu.correctPos.x = inventoryMenu.pos.x - (inventoryMenu.img->GetFrameWidth() / 2);
	inventoryMenu.correctPos.y = inventoryMenu.pos.y - (inventoryMenu.img->GetFrameHeight() / 2);
	SetRect(&inventoryMenu.rect, inventoryMenu.pos,
		(inventoryMenu.img->GetFrameWidth(), (inventoryMenu.img->GetFrameHeight())));

	item = ImageManager::GetSingleton()->FindImage
	("Image/Inventory/Inventory_Item.bmp", 96, 48, 6, 3);
}

bool InventoryManager::Uadate()
{
	if (GET_KEY_DOWN('E'))activeCheck = !activeCheck;
	if (activeCheck == false) return false;

	RECT rect;
	mouse = g_ptMouse;
	POINT view;
	GetClientRect(g_hWnd, &rect);
	view.x = rect.right - rect.left;
	view.y = rect.bottom - rect.top;
	if (view.x != WIN_SIZE_X || view.y != WIN_SIZE_Y)
	{
		view.x /= WIN_SIZE_X;
		view.y /= WIN_SIZE_Y;
		mouse.x /= view.x;
		mouse.y /= view.y;
	}

	if (GET_KEY_DOWN(VK_LBUTTON))
	{
		mouseClick = GetInventoryNum(mouse).second;
	}

	return true;
}

void InventoryManager::Render(HDC hdc)
{
	if (activeCheck == false) return;

	// �κ��丮 ����â ����
	inventoryMain.img->Render(hdc,
		inventoryMain.pos.x, 
		inventoryMain.pos.y,
		0,0);
	
	// �κ��丮 �޴�â ����
	inventoryMenu.img->Render(hdc,
		inventoryMenu.pos.x,
		inventoryMenu.pos.y,
		0, 0);

	for (int y = 0; y < INVEN_SIZE_Y; ++y)
	{
		for (int x = 0; x < INVEN_SIZE_X; ++x)
		{
			if (inventory[y][x].first.GetItemType() != ItemType::Empty)
			{	// �κ��丮�� �������� ���� ���
				if (mouseClick.x == x && mouseClick.y == y)
				{	// ���콺�� �κ��丮 �������� Ŭ���� ��� �϶� ��� ����
					continue;
				}
				int space = y >= 1 ? 4 : 0;
				int posX = inventoryMain.pos.x - (inventoryMain.img->GetFrameWidth() / 2) + SPACE_X + (x * TILE_SIZE) + 9;
				int posY = inventoryMain.pos.y - (inventoryMain.img->GetFrameHeight() / 2) + SPACE_Y + (y * TILE_SIZE) + 8 + space;
				POINT frame = inventory[y][x].first.GetFrame();
				item->Render(hdc, posX, posY, frame.x, frame.y);
				// ������ ���

				int number = inventory[y][x].second;
				char num_char[10 + sizeof(char)];
				sprintf_s(num_char, "%d", number);
				OnBnClickedOk(hdc, num_char, posX, posY);
				// ������ ���� ���
			}
		}
	}

	if (mouseClick.x != -1 && mouseClick.y != -1)
	{	// ���콺�� Ŭ��, �巡���� �κ��丮 ������ ���
		POINT frame = inventory[mouseClick.y][mouseClick.x].first.GetFrame();
		item->Render(hdc, mouse.x, mouse.y, frame.x, frame.y);
		// ������ ���

		int number = inventory[mouseClick.y][mouseClick.x].second;
		char num_char[10 + sizeof(char)];
		sprintf_s(num_char, "%d", number);
		OnBnClickedOk(hdc, num_char, mouse.x, mouse.y);
		// ������ ���� ���
	}
	
	if (GET_KEY_UP(VK_LBUTTON) && mouseClick.x >= 0 && mouseClick.y >= 0)
	{
		pair<bool, POINT> result = GetInventoryNum(mouse);
		if (result.first == false)
		{	// ���콺�� �������� ����� �������� �κ�â ���̶��
			ITEM_MANAGER->CreateResourceItem(
				inventory[mouseClick.y][mouseClick.x].first.GetItemCode(),
				GAMEDATA_MANAGER->GetPlayerPos(), 
				inventory[mouseClick.y][mouseClick.x].second);

			inventory[mouseClick.y][mouseClick.x].first.Release();
			inventory[mouseClick.y][mouseClick.x].second = 0;
		}
		else if (result.second.x >= 0 && result.second.y >= 0)
		{	// ���콺�� �������� ����� �������� �κ�â �� �̶��
			swap(inventory[mouseClick.y][mouseClick.x], inventory[result.second.y][result.second.x]);
		}
		mouseClick = { -1,-1 };
	}
}

void InventoryManager::Release()
{
	ReleaseSingleton();
}
