#include "Item.h"
#include "Image.h"
#include "Config.h"
bool Item::PlayerFollow()
{
	static POINTFLOAT playerPos;
	static float distance;
	static float xSpeed;
	static float ySpeed;

	playerPos = GAMEDATA_MANAGER->GetPlayerPos();
	distance = (float)sqrt(pow(pos.x - playerPos.x, 2) + pow(pos.y - playerPos.y, 2));
	// 플레이어까지 직선거리

	if (distance < 30.0f)
	{
		pos.x -= (playerPos.x - pos.x) * (distance - 30) * 0.2f * DELTA_TIME;
		pos.y -= (playerPos.y - pos.y) * (distance - 30) * 0.2f * DELTA_TIME;
	}
	// 플레이어까지의 거리가 30 이하라면 플레이어 추적

	if (distance < 5.0f)
		return true;

	return false;
}

void Item::GravityAction()
{
	static bool xCheck;
	xCheck = move.speed.x > 0.0f ? true : false;
	if (xCheck)
	{
		if (fabs(move.speed.x) > 0.1f)
		{
			move.speed.x -= 4 * DELTA_TIME;
			pos.x += move.speed.x * DELTA_TIME;
		}
	}
	else
	{
		if (fabs(move.speed.x) > 0.1f)
		{
			move.speed.x += 4 * DELTA_TIME;
			pos.x += move.speed.x * DELTA_TIME;
		}
	}

	if (!(move.landPos <= pos.y && fabs(move.speed.y) < 30) && move.gravityCheck)
	{
		move.speed.y += move.gravity * DELTA_TIME;
		if (move.landPos <= pos.y && move.speed.y >= 30)
		{
			move.speed.y *= -0.7f;
		}
		pos.y += move.speed.y * DELTA_TIME;
	}
	else
	{
		move.gravityCheck = false;
	}
}

HRESULT Item::Init()
{
	move.landPos = pos.y + 2;
	
	move.speed.x = (float)(5 + (rand() % 3));
	move.speed.y = (float)((60 + (rand() % 10))*-1);
	if (rand() % 2) { move.speed.x *= -1; }
	move.gravity = 200.0f;
	itemType = ItemType::ResourceItem;
	img = ImageManager::GetSingleton()->FindImage("Image/Stones/Stone_Object_Item.bmp", 192, 16, 12, 1);
	return S_OK;
}

void Item::Update()
{
	GravityAction();
	if (move.time > 0.4f)
	{
		if (PlayerFollow())
		{
			INVEN_MANAVER->InventoryPush(&info, &itemType, 1, 1);
			ITEM_MANAGER->DeleteObjectVector(this);
			Release();
			return;
		}
	}
	else
	{
		move.time += DELTA_TIME;
	}
}

void Item::Render(HDC hdc)
{
	img->Render(hdc, pos.x - GLOBAL_POS.x, pos.y - GLOBAL_POS.y, 0, 0);

}

void Item::Release()
{
	RENDER_MANAGER->DeleteObjectVector(this);
	delete this;
}

Item::Item(int key, POINTFLOAT pos, int itemNum) :
	itemType{ ItemType::ToolItem },  itemNum{ itemNum }

{
	this->pos = pos;
	Init();
	info = ITEM_MANAGER->GetResourceItem(key);
	RENDER_MANAGER->PushObjectVector(this);
};
