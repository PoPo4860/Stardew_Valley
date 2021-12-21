#include "SmallStone.h"
#include "Config.h"
#include "CommonFunction.h"
#include "image.h"
SmallStone::SmallStone(Stone_Object_Info obj, int x, int y) :frame{ NULL }, objectInfo{ obj }
{
	pos.x = (float)x, pos.y = (float)y;
	RENDER_MANAGER->PushObjectVector(this);
	Init(); 
}
bool SmallStone::InteractionPick(int damage)
{
	hp -= damage;

	return false;
}

HRESULT SmallStone::Init()
{
	img = ImageManager::GetSingleton()->FindImage("Image/Stones/Stone_Object.bmp",192,64,12,4);
	pos.x = (pos.x * 16) + 8;
	pos.y = (pos.y * 16) + 8;
	bodySize = 16;
	SetRect(&rect, pos, bodySize);

	if (objectInfo == Stone_Object_Info::SmallStone_Lv1)
	{
		frame = rand() % 3;
		hp = 1;
	}
	else if (objectInfo == Stone_Object_Info::SmallStone_Lv2)
	{
		hp = 2;
	}
	else if (objectInfo == Stone_Object_Info::SmallStone_Lv3)
	{
		hp = 3;
	}
	return S_OK;
}

void SmallStone::Update()
{
	if (hp <= 0)
	{
		CreateItem();
		Release();
	}
}

void SmallStone::Render(HDC hdc)
{
	if(hp > 0)
		img->Render(hdc, 
			pos.x - GLOBAL_POS.x, 
			pos.y - GLOBAL_POS.y, 
			frame, 
			0);
}

void SmallStone::Release()
{
	POINT result = GetPosTile(pos, MAP->mapSizeY, MAP->mapSizeX);
	MAP_MANAGER->DeleteMapObject(result);
    RENDER_MANAGER->DeleteObjectVector(this);
	delete this;
}

void SmallStone::CreateItem()
{
	ITEM_MANAGER->CreateResourceItem(STONE, pos);
	ITEM_MANAGER->CreateResourceItem(COAL, pos);
}
