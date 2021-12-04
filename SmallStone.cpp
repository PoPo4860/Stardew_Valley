#include "SmallStone.h"
#include "Config.h"
#include "image.h"
bool SmallStone::InteractionPick(int damage)
{
	hp -= damage;
	if (hp < 0) return true;
	return false;
}

HRESULT SmallStone::Init()
{
	img = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Stone_Object.bmp");
	pos.x = (pos.x * 16) + 8 - GLOBAL_POS.x;
	pos.y = (pos.y * 16) + 8 - GLOBAL_POS.y;
	bodySize = 16;
	rect.left = pos.x - (bodySize / 2);
	rect.right = pos.x + (bodySize / 2);
	rect.top = pos.y - (bodySize / 2);
	rect.bottom = pos.y + (bodySize / 2);
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
