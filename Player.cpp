#include "Player.h""
#include "Image.h"
#include "Config.h"
#include "CommonFunction.h"
Player::Player():
	mapPos{},
	moveCheck{ false },
	frameX{ NULL },
	time{ NULL },
	moveDirection{ MoveDirection::Down }
{
}
HRESULT Player::Init()
{
	img = ImageManager::GetSingleton()->FindImage("Image/Player/Player_Move.bmp", 128, 128, 8, 4);
	pos.x = 100.0f;
	pos.y = 150.0f;
	moveSpeed = 70.0f;
	bodySize = 10;
	return S_OK;
}

void Player::Update()
{
	time += DELTA_TIME;
	SetRect(&rect,pos,bodySize);
	//rect.left = pos.x - (bodySize / 2);
	//rect.right = pos.x + (bodySize / 2);
	//rect.top = pos.y - (bodySize / 2);
	//rect.bottom = pos.y + (bodySize / 2);
	moveCheck = false;

	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_UP))
	{
		moveDirection = MoveDirection::Up;
		Move(pos.x, pos.y - (moveSpeed * DELTA_TIME));
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN))
	{
		moveDirection = MoveDirection::Down;
		Move(pos.x, pos.y + (moveSpeed * DELTA_TIME));
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
	{
		moveDirection = MoveDirection::Left;
		Move(pos.x - (moveSpeed * DELTA_TIME), pos.y);
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
	{
		moveDirection = MoveDirection::Right;
		Move(pos.x + (moveSpeed * DELTA_TIME), pos.y);
	}
	ObjectPosManager::GetSingleton()->SetGlobalPos(pos);
	//플레이어 기준으로 글로벌 좌표를 재설정 한다.
}

void Player::Render(HDC hdc)
{
	int frame = frameX;
	if (moveDirection == MoveDirection::Left || moveDirection == MoveDirection::Right)
	{
		frame %= 6;
	}
	else if (moveDirection == MoveDirection::Up || moveDirection == MoveDirection::Down)
	{
		frame %= 8;
	}
	if (moveCheck)
	{
		img->Render(hdc,
			pos.x - GLOBAL_POS.x,
			pos.y - bodySize - GLOBAL_POS.y,
			frame, moveDirection);
	}
	else
	{
		img->Render(hdc,
			pos.x - GLOBAL_POS.x,
			pos.y - bodySize - GLOBAL_POS.y,
			0, moveDirection);
	}

}

void Player::Release()
{
}

void Player::Move(float posX, float posY)
{
	moveCheck = true;

	if (time > 0.3f)
	{
		time = 0.0f;
		frameX = 0;
	}
	else if (time > 0.1f)
	{
		time = 0.0f;
		++frameX;
		if (frameX >= 8 * 6) frameX -= 8 * 6;
	}
	RECT rectTemp;
	POINTFLOAT posTemp;
	posTemp.x = posX;
	posTemp.y = posY;
	SetRect(&rectTemp, posTemp, bodySize);

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
