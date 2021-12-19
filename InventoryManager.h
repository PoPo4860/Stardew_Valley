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
class InventoryManager : public Singleton<InventoryManager>
{
private:
	pair<InventoryItem, int> inventory[INVEN_SIZE_Y][INVEN_SIZE_X];
	InventoryImage inventoryMain;
	InventoryImage inventoryMenu;
	Image* item;
	bool activeCheck;
	POINT mouse;
	POINT mouseClick;

	pair<bool,POINT> GetInventoryNum(POINT mouse);
public:
	InventoryManager();
	void Init();
	void Render(HDC hdc);
	bool Uadate();
	void Release();
public:
	void InventoryPush(ToolItemInfo* item, ItemType* type, int itemCode, int itemNum);
	void InventoryPush(ResourceItemInfo* item, ItemType* type, int itemCode, int itemNum);
	int InventoryAdd(int itemCode, int itemNum);
	POINT InventoryEmptyAdd(ItemType* type, int itemCode, int itemNum);
	bool InventoryEmptyCheck();
};

