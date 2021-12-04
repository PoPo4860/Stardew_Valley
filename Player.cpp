#include "Player.h"
#include "ImageManager.h"
#include "TimerManager.h"
#include "KeyManager.h"
#include "Image.h"
HRESULT Player::Init()
{
	ImageManager::GetSingleton()->AddImage
	("Image/Player.bmp", 10, 10, 1, 1, true, RGB(255, 0, 255));
	img = ImageManager::GetSingleton()->FindImage("Image/Player.bmp");
	pos.x = 100.0f;
	pos.y = 150.0f;
	moveSpeed = 100.0f;
	bodySize = 10;
	return S_OK;
}

void Player::Update()
{
	rect.left = pos.x - (bodySize / 2);
	rect.right = pos.x + (bodySize / 2);
	rect.top = pos.y - (bodySize / 2);
	rect.bottom = pos.y + (bodySize / 2);

	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_UP))
		Move(pos.x, pos.y - (moveSpeed * TIME));
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN))
		Move(pos.x, pos.y + (moveSpeed * TIME));
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
		Move(pos.x - (moveSpeed * TIME), pos.y);
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
		Move(pos.x + (moveSpeed * TIME), pos.y);
	ObjectPosManager::GetSingleton()->SetGlobalPos(pos);
}

void Player::Render(HDC hdc)
{
	img->Render(hdc, pos.x - GLOBAL_POS.x, pos.y - GLOBAL_POS.y, 0, 0);
}

void Player::Release()
{
}

void Player::Move(float posX, float posY)
{
	RECT rectTemp;
	rectTemp.left = posX - (bodySize / 2);
	rectTemp.right = posX + (bodySize / 2);
	rectTemp.top = posY - (bodySize / 2);
	rectTemp.bottom = posY + (bodySize / 2);
	for (int y = 0; y < MAP->mapSizeY; ++y)
	{
		for (int x = 0; x < MAP->mapSizeX; ++x)
		{
			if (MAP->tileState[y][x] != Tile_State::Empty)
			{
				RECT rc;
				if (IntersectRect(&rc, &rectTemp, &MAP->rect[y][x]))
					return;
			}
			if (MAP->object[y][x] != nullptr)
			{
				RECT rc;
				RECT temp = MAP->object[y][x]->GetRect();
				if (IntersectRect(&rc, &rectTemp, &temp))
					return;
			}
		}
	}
	pos.x = posX;
	pos.y = posY;
}	
