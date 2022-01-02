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
{ }

void InventoryManager::PushInventory(int itemCode, int itemNum)
{
	itemNum = AddInventory(itemCode, itemNum);
	if (itemNum > 0)
	{
		POINT retult = AddInventoryEmpty(itemCode, itemNum);
		inventory[retult.y][retult.x].itemCode = itemCode;
	}
}

int InventoryManager::AddInventory(int itemCode, int itemNum)
{
	// ���� ������ �������� �κ��丮�� �ְ�, �ִ밹������ ���ٸ� �����߰�
	for (int y = 0; y < INVEN_SIZE_Y; ++y)
	{
		for (int x = 0; x < INVEN_SIZE_X; ++x)
		{
			if (inventory[y][x].itemCode == itemCode &&
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

POINT InventoryManager::AddInventoryEmpty(int itemCode, int itemNum)
{	// ����ִ� ���� �������� �߰��ϰ�, �� ��ġ ��ȯ
	POINT result{ -1,-1 };

	for (int y = 0; y < INVEN_SIZE_Y; ++y)
	{
		for (int x = 0; x < INVEN_SIZE_X; ++x)
		{
			if (inventory[y][x].itemCode == 0)
			{
				inventory[y][x].itemCode = itemCode;
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
			if (inventory[y][x].itemCode == 0)
			{
				return true;
			}
		}
	}
	return false;
}

void InventoryManager::RenderItem(HDC hdc, POINT inventoryNum, POINT pos)
{
	int itemCode = inventory[inventoryNum.y][inventoryNum.x].itemCode;
	if (itemCode == 0)
	{
		return;
	}
	ITEM_MANAGER->ItemRender(hdc, itemCode, pos.x, pos.y);

	// ������ ���� ���
	int number = inventory[inventoryNum.y][inventoryNum.x].itemNum;
	if (number != 0)
	{
		char num_char[10 + sizeof(char)];
		sprintf_s(num_char, "%d", number);
		PrintText(hdc, num_char, pos.x, pos.y);
	}
}

void InventoryManager::Init()
{
	inventoryMain.img = ImageManager::GetSingleton()->FindImage("Image/Inventory/Inventory_Main.bmp", 213, 146, 1, 1);
	inventoryMain.pos.x = (WIN_SIZE_X / 2); inventoryMain.pos.y = (WIN_SIZE_Y / 2);
	inventoryMain.correctPos.x = (LONG)(inventoryMain.pos.x - (inventoryMain.img->GetFrameWidth() / 2));
	inventoryMain.correctPos.y = (LONG)(inventoryMain.pos.y - (inventoryMain.img->GetFrameHeight() / 2));
	SetRect(&inventoryMain.rect,inventoryMain.pos, 
		(inventoryMain.img->GetFrameWidth()), (inventoryMain.img->GetFrameHeight()));

	PushInventory(PICK, 1);
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
			if (inventory[y][x].itemCode != 0)
			{	// �κ��丮�� �������� ���� ���
				if (mouseClick.x == x && mouseClick.y == y)
				{	// ���콺�� �κ��丮 �������� Ŭ���� ��� �϶� ��� ����
					continue;
				}
				// ������ ���
				int space = y >= 1 ? 4 : 0;
				int posX = (int)inventoryMain.pos.x - (inventoryMain.img->GetFrameWidth() / 2) + SPACE_X + (x * TILE_SIZE) + 9;
				int posY = (int)inventoryMain.pos.y - (inventoryMain.img->GetFrameHeight() / 2) + SPACE_Y + (y * TILE_SIZE) + 8 + space;
				RenderItem(hdc, POINT{ x, y }, POINT{ posX, posY });
			}
		}
	}

	if (mouseClick.x != -1 && mouseClick.y != -1)
	{	// ���콺�� Ŭ��, �巡���� �κ��丮 ������ ���
		int itemCode = inventory[mouseClick.y][mouseClick.x].itemCode;
		RenderItem(hdc, mouseClick, mouse);
	}
	
	if (GET_KEY_UP(VK_LBUTTON) && mouseClick.x >= 0 && mouseClick.y >= 0)
	{
		InventoryMouse result = GetInventoryNum(mouse);
		if (result.inInventory == false)
		{	// ���콺�� �������� ����� �������� �κ�â ���̶��
			ITEM_MANAGER->CreateResourceItem(
				inventory[mouseClick.y][mouseClick.x].itemCode,
				GAMEDATA_MANAGER->GetPlayerPos(), 
				inventory[mouseClick.y][mouseClick.x].itemNum);

			inventory[mouseClick.y][mouseClick.x].itemCode = 0;
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
