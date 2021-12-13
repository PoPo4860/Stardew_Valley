#include "ResourceItem.h"
#include "Config.h"
#include "Image.h"
ResourceItem::ResourceItem(int key, POINTFLOAT pos)
{
	this->pos = pos;
	Init();
	ItemInit();
	info = ITEM_MANAGER->GetResourceItem(key);
}

HRESULT ResourceItem::Init()
{
	itemInfo = ItemInfo::ResourceItem;
	img = ImageManager::GetSingleton()->FindImage("Image/Stones/Stone_Object_Item.bmp", 192, 16, 12, 1);
	return S_OK;
}

void ResourceItem::Update()
{
	PlayerFollow();
	GravityAction();
}

void ResourceItem::Render(HDC hdc)
{
	img->Render(hdc, pos.x - GLOBAL_POS.x, pos.y - GLOBAL_POS.y, 0, 0);
}

void ResourceItem::Release()
{
}
