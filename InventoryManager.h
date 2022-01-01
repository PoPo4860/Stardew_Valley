#pragma once
#include "Config.h"
#include "ItemCode.h"
#include "InventoryItem.h"
#define INVEN_SIZE_X 12
#define INVEN_SIZE_Y 3
class Image;
struct InventoryImage
{
	Image* img;			// �̹���
	POINTFLOAT pos;		// ���� ��µǴ� ��ǥ
	RECT rect;			// ���� Rect
	POINT correctPos;	// ���� ��ǥ
};
struct Inventory
{
	InventoryItem item;	// ������
	int itemNum = 0;	// ������ ����
};
struct InventoryMouse
{
	bool inInventory;
	POINT mouse;
};
class InventoryManager : public Singleton<InventoryManager>
{
private:
	Inventory inventory[INVEN_SIZE_Y][INVEN_SIZE_X];
	InventoryImage inventoryMain;
	InventoryImage inventoryMenu;
	bool activeCheck;
	POINT mouse;
	POINT mouseClick;

	InventoryMouse GetInventoryNum(POINT mouse);
public:
	InventoryManager();
	void Init();
	void Render(HDC hdc);
	bool Uadate();
	void Release();
public:
	const void PushInventory(const ToolItemInfo* item, ItemType* type, int itemCode, int itemNum);
	const void PushInventory(const ResourceItemInfo* item, ItemType* type, int itemCode, int itemNum);
	int AddInventory(int itemCode, int itemNum);
	POINT AddInventoryEmpty(ItemType* type, int itemCode, int itemNum);
	bool CheckInventoryEmpty();

	void RenderItem(HDC hdc, POINT inventoryNum, POINT pos);
};

