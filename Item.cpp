#include "Item.h"
#include "Config.h"
void Item::PlayerFollow()
{
	static POINTFLOAT playerPos;
	static float distance;
	static float xSpeed;
	static float ySpeed;

	playerPos = GAMEDATA_MANAGER->GetPlayerPos();
	distance = sqrt(pow(pos.x - playerPos.x, 2) + pow(pos.y - playerPos.y, 2));
	// 플레이어까지 직선거리

	if (distance < 30.0f)
	{
		pos.x -= (playerPos.x - pos.x) * (distance - 30) * 0.2f * DELTA_TIME;
		pos.y -= (playerPos.y - pos.y) * (distance - 30) * 0.2f * DELTA_TIME;
	}
	// 플레이어까지의 거리가 30 이하라면 플레이어 추적
}

void Item::GravityAction()
{
	static bool xCheck = moveSpeed.x > 0.0f ? true : false;
	if (xCheck)
	{
		if (moveSpeed.x > 0.1f)
		{
			moveSpeed.x -= (DELTA_TIME * 2);
			pos.x += moveSpeed.x;
		}
	}
	else
	{
		if (moveSpeed.x < -0.1f)
		{
			moveSpeed.x += (DELTA_TIME * 2);
			pos.x += moveSpeed.x;
		}
	}
	static bool yCheck = true;
	if (yCheck)
	{
		pos.y += gravity * DELTA_TIME;
	}
	else
	{
		 
	}
}

void Item::ItemInit()
{
	landPos.x = pos.x;
	landPos.y = pos.y - 5;
	
	float xSpeed = 5 + (rand() % 3);
	float ySpeed = 10 + (rand() % 10);
	if (rand() % 2) { xSpeed *= -1; }
	moveSpeed.x = xSpeed;
	moveSpeed.y = ySpeed;
	gravity = 20.0f + ((rand() % 50) / 10);
	// 20 ~ 25 사이의 중력값 랜덤설정
}

Item::Item() :itemInfo{ ItemInfo::ToolItem }, gravity{ }, landPos{} 
{
};