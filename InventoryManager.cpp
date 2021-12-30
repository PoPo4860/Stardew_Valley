#include "InventoryManager.h"
#include "CommonFunction.h"
#include "Image.h"

#define SPACE_X 11
#define SPACE_Y 10

InventoryMouse InventoryManager::GetInventoryNum(POINT mouse)
{
	bool check = false;
	POINT num{ -1,-1 };
	if (PtInRect(&(inventoryMain.rect), mouse))
	{	// �κ��丮 ���ο����� ���
		mouse.x -= inventoryMain.correctPos.x;
		mouse.y -= inventoryMain.correctPos.y;
		if (SPACE_X <= mouse.x && mouse.x <= SPACE_X + (TILE_SIZE * INVEN_SIZE_X))
		{
			num.x = (LONG)(mouse.x - SPACE_X) / 16;
		}
		if (SPACE_Y <= mouse.y && mouse.y <= SPACE_Y + TILE_SIZE)
		{
			num.y = 0;
		}
		else if (SPACE_Y + TILE_SIZE + 4 <= mouse.y && mouse.y <= SPACE_Y + (TILE_SIZE * 2) + 4)
		{
			num.y = 1;
		}
		else if (SPACE_Y + (TILE_SIZE * 2) + 5 <= mouse.y && mouse.y <= SPACE_Y + (TILE_SIZE * 3) + 5)
		{
			num.y = 2;
		}
		check = true;
	}
	return InventoryMouse{ check, num };
}
InventoryManager::InventoryManager()
	:inventory{}, inventoryMain{}, inventoryMenu{}, mouseClick{ -1,-1 }, activeCheck{ false }
{Init(); }

const void InventoryManager::PushInventory(const ToolItemInfo* item ,ItemType* type, int itemCode, int itemNum)
{
	itemNum = AddInventory(itemCode, itemNum);
	if (itemNum > 0)
	{
		POINT retult = AddInventoryEmpty(type, itemCode, itemNum);
		inventory[retult.y][retult.x].item.SetToolItemInfo(*item);
	}
}

const void InventoryManager::PushInventory(const ResourceItemInfo* item, ItemType* type, int itemCode, int itemNum)
{
	itemNum = AddInventory(itemCode , itemNum);
	if (itemNum > 0)
	{
		POINT retult = AddInventoryEmpty(type, itemCode, itemNum);
		inventory[retult.y][retult.x].item.SetResourceItemInfo(*item);
	}
}

int InventoryManager::AddInventory(int itemCode, int itemNum)
{
	// ���� ������ �������� �κ��丮�� �ְ�, �ִ밹������ ���ٸ� �����߰�
	for (int y = 0; y < INVEN_SIZE_Y; ++y)
	{
		for (int x = 0; x < INVEN_SIZE_X; ++x)
		{
			if (inventory[y][x].item.GetItemCode() == itemCode &&
				inventory[y][x].itemNum < 64)
			{
				inventory[y][x].itemNum += itemNum;
				if (inventory[y][x].itemNum >= 64)
				{
					itemNum = inventory[y][x].itemNum - 64;
					inventory[y][x].itemNum -= itemNum;
				}
				else
				{
					return 0;
				}
			}	
		}
	}
	return itemNum;
}

POINT InventoryManager::AddInventoryEmpty(ItemType* type, int itemCode, int itemNum)
{	// ����ִ� ���� �������� �߰��ϰ�, �� ��ġ ��ȯ
	POINT result;
	result.x = 0;
	result.y = 0;
	for (int y = 0; y < INVEN_SIZE_Y; ++y)
	{
		for (int x = 0; x < INVEN_SIZE_X; ++x)
		{
			if (inventory[y][x].item.GetItemType() == ItemType::Empty)
			{
				inventory[y][x].item.SetItemCode(itemCode);
				inventory[y][x].item.SetItemType(*type);
				inventory[y][x].itemNum = itemNum;
				result.x = x;
				result.y = y;
				return result;
			}
		}
	}	
	return result;
}

bool InventoryManager::CheckInventoryEmpty()
{
	for (int y = 0; y < INVEN_SIZE_Y; ++y)
	{
		for (int x = 0; x < INVEN_SIZE_X; ++x)
		{
			if (inventory[y][x].item.GetItemType() == ItemType::Empty) return true;
		}
	}
	return false;
}

void InventoryManager::Init()
{
	inventoryMain.img = ImageManager::GetSingleton()->FindImage("Image/Inventory/Inventory_Main.bmp", 213, 146, 1, 1);
	inventoryMain.pos.x = (WIN_SIZE_X / 2); inventoryMain.pos.y = (WIN_SIZE_Y / 2);
	inventoryMain.correctPos.x = (LONG)(inventoryMain.pos.x - (inventoryMain.img->GetFrameWidth() / 2));
	inventoryMain.correctPos.y = (LONG)(inventoryMain.pos.y - (inventoryMain.img->GetFrameHeight() / 2));
	SetRect(&inventoryMain.rect,inventoryMain.pos, 
		(inventoryMain.img->GetFrameWidth()), (inventoryMain.img->GetFrameHeight()));
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
		mouseClick = GetInventoryNum(mouse).mouse;
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
	//inventoryMenu.img->Render(hdc,
	//	inventoryMenu.pos.x,
	//	inventoryMenu.pos.y,
	//	0, 0);

	for (int y = 0; y < INVEN_SIZE_Y; ++y)
	{
		for (int x = 0; x < INVEN_SIZE_X; ++x)
		{
			if (inventory[y][x].item.GetItemType() != ItemType::Empty)
			{	// �κ��丮�� �������� ���� ���
				if (mouseClick.x == x && mouseClick.y == y)
				{	// ���콺�� �κ��丮 �������� Ŭ���� ��� �϶� ��� ����
					continue;
				}
				int space = y >= 1 ? 4 : 0;
				int posX = (int)inventoryMain.pos.x - (inventoryMain.img->GetFrameWidth() / 2) + SPACE_X + (x * TILE_SIZE) + 9;
				int posY = (int)inventoryMain.pos.y - (inventoryMain.img->GetFrameHeight() / 2) + SPACE_Y + (y * TILE_SIZE) + 8 + space;
				POINT frame = inventory[y][x].item.GetFrame();
				item->Render(hdc, posX, posY, frame.x, frame.y);
				// ������ ���

				int number = inventory[y][x].itemNum;
				char num_char[10 + sizeof(char)];
				sprintf_s(num_char, "%d", number);
				PrintText(hdc, num_char, posX, posY);
				// ������ ���� ���
			}
		}
	}

	if (mouseClick.x != -1 && mouseClick.y != -1)
	{	// ���콺�� Ŭ��, �巡���� �κ��丮 ������ ���
		POINT frame = inventory[mouseClick.y][mouseClick.x].item.GetFrame();
		item->Render(hdc, mouse.x, mouse.y, frame.x, frame.y);
		// ������ ���

		int number = inventory[mouseClick.y][mouseClick.x].itemNum;
		char num_char[10 + sizeof(char)];
		sprintf_s(num_char, "%d", number);
		PrintText(hdc, num_char, mouse.x, mouse.y);
		// ������ ���� ���
	}
	
	if (GET_KEY_UP(VK_LBUTTON) && mouseClick.x >= 0 && mouseClick.y >= 0)
	{
		InventoryMouse result = GetInventoryNum(mouse);
		if (result.inInventory == false)
		{	// ���콺�� �������� ����� �������� �κ�â ���̶��
			ITEM_MANAGER->CreateResourceItem(
				inventory[mouseClick.y][mouseClick.x].item.GetItemCode(),
				GAMEDATA_MANAGER->GetPlayerPos(), 
				inventory[mouseClick.y][mouseClick.x].itemNum);

			inventory[mouseClick.y][mouseClick.x].item.Release();
			inventory[mouseClick.y][mouseClick.x].itemNum = 0;
		}
		else if (result.mouse.x >= 0 && result.mouse.y >= 0)
		{	// ���콺�� �������� ����� �������� �κ�â �� �̶��
			swap(inventory[mouseClick.y][mouseClick.x], inventory[result.mouse.y][result.mouse.x]);
		}
		mouseClick = { -1,-1 };
	}
}

void InventoryManager::Release()
{
	ReleaseSingleton();
}
