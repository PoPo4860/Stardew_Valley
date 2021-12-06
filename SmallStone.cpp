#include "SmallStone.h"
#include "Config.h"
#include "CommonFunction.h"
#include "image.h"
bool SmallStone::InteractionPick(int damage)
{
	hp -= damage;
	if (hp < 0) return true;
	return false;
}

HRESULT SmallStone::Init()
{
	img = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Stone_Object.bmp",192,64,12,4);
	pos.x = (pos.x * 16) + 8;
	pos.y = (pos.y * 16) + 8;
	bodySize = 16;
	SetRect(&rect,pos,bodySize);

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
}

void SmallStone::Render(HDC hdc)
{
	img->Render(hdc, pos.x - GLOBAL_POS.x, pos.y - GLOBAL_POS.y, frame, 0);
}

void SmallStone::Release()
{
}
