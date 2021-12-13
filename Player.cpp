#pragma once
#include "Player.h""
#include "Image.h"
#include "Config.h"
#include "CommonFunction.h"

// 메세지루프와 인풋

Player::Player() :
	direction{ MoveDirection::Down },
	playerState{PlayerState::Normal},
	actionCheck{ false },
	frameX{ NULL },
	time{ NULL },
	playerImage{ }
{}

HRESULT Player::Init()
{
	for (int y = 0; y < MAP->mapSizeY; ++y)
	{
		bool check = false;
		for (int x = 0; x < MAP->mapSizeX; ++x)
		{
			if (MAP_MANAGER->GetMap()->tileState[y][x] == Tile_State::LadderUp)
			{
				pos.x = (float)((x + 1) * TILE_SIZE - (TILE_SIZE / 2));
				pos.y = (float)((y + 1) * TILE_SIZE + (TILE_SIZE / 2));
				check = true;
				break;
			}
			if (check) break;
		}
	}
	
	playerImage.move = ImageManager::GetSingleton()->FindImage("Image/Player/Player_Move.bmp", 128, 128, 8, 4);
	playerImage.pick = ImageManager::GetSingleton()->FindImage("Image/Player/Player_Pick.bmp", 80, 128, 5, 4);
	//pos.x = 100.0f;
	//pos.y = 150.0f;
	moveSpeed = 70.0f;
	bodySize = 10;
	return S_OK;
}

void Player::Update()
{
	time += DELTA_TIME;
	if (actionCheck == false)
	{
		if (KeyManager::GetSingleton()->IsStayKeyDown('C'))
		{
			playerState = PlayerState::Pick;
			actionCheck = true;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('X'))
		{
			POINT result = GetFrontTilePos();
			
			MAP_MANAGER->Interaction(result);
		} 
		else 
		{
			playerState = PlayerState::Normal;
		}
	}
	
	SetRect(&rect, pos, bodySize);
	switch (playerState) {
	case PlayerState::Normal:
		StateNormalUpdate();
		break;
	case PlayerState::Pick:
		StatePickUpdate();
		break;
	}

	ObjectPosManager::GetSingleton()->SetGlobalPos(pos);
	GAMEDATA_MANAGER->SetPlayerPos(pos);

}

void Player::Render(HDC hdc)
{
	int frame = GetFrame();
	// 각 렌더에 적용할 프레임 

	switch (playerState) {
	case PlayerState::Normal:
		StateNormalRender(hdc, frame);
		break;
	case PlayerState::Pick:
		StatePickRender(hdc, frame);
		break;
	}
}

void Player::Release()
{
}

void Player::Move(float posX, float posY)
{
	RECT rectTemp;
	POINTFLOAT posTemp;
	posTemp.x = posX;
	posTemp.y = posY;
	SetRect(&rectTemp, posTemp, bodySize);
	// 플레이어 충돌체크할 RECT 생성

	POINT result = GetPosTile(pos);
	// 자기 pos값을 기준으로, 몇번째 타일인지 확인하는 함수

	for (int y = result.y - 2; y < result.y + 2; ++y)
	{
		for (int x = result.x - 2; x < result.x + 2; ++x)
		{
			if (MAP->tileState[y][x] != Tile_State::Empty)
			{	// 해당 타일이 비어있는 공간이 아니라면 충돌검사
				RECT rc;
				if (IntersectRect(&rc, &rectTemp, &MAP->rect[y][x]))
					return;
			}
			if (MAP->object[y][x] != nullptr)
			{	// 해당 타일에 오브젝트가 있다면 충돌검사
				RECT rc;
				RECT temp = MAP->object[y][x]->GetRect();
				if (IntersectRect(&rc, &rectTemp, &temp))
					return;
			}
		}
	}

	pos.x = posX;
	pos.y = posY;
	// 충돌이 생기지 않았다면 바뀐 pos로 적용
}

void Player::StateNormalUpdate()
{
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_UP))
	{
		direction = MoveDirection::Up;
		Move(pos.x, pos.y - (moveSpeed * DELTA_TIME));
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN))
	{
		direction = MoveDirection::Down;
		Move(pos.x, pos.y + (moveSpeed * DELTA_TIME));
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
	{
		direction = MoveDirection::Left;
		Move(pos.x - (moveSpeed * DELTA_TIME), pos.y);
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
	{
		direction = MoveDirection::Right;
		Move(pos.x + (moveSpeed * DELTA_TIME), pos.y);
	}
}
void Player::StateNormalRender(HDC hdc, int frame)
{
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_UP)|| KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN) ||
		KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT) || KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
	{
		playerImage.move->Render(hdc,
			pos.x - GLOBAL_POS.x,
			pos.y - bodySize - GLOBAL_POS.y,
			frame, direction);
	}
	else
	{
		playerImage.move->Render(hdc,
			pos.x - GLOBAL_POS.x,
			pos.y - bodySize - GLOBAL_POS.y, 
			0, direction);
	}
}

void Player::StatePickUpdate()
{

}
void Player::StatePickRender(HDC hdc, int frame) {
	static bool actionCheck = false;
	if (frame == 4 && actionCheck == false)
	{
		ActionPick();
		actionCheck = true;
		COUT;;
	}
	else if (frame != 4)
	{
		actionCheck = false;
	}
	
	playerImage.pick->Render(hdc,
		pos.x - GLOBAL_POS.x,
		pos.y - bodySize - GLOBAL_POS.y,
		frame,
		direction);
}
POINT Player::GetFrontTilePos()
{
	POINT result = GetPosTile(pos, MAP->mapSizeX, MAP->mapSizeY);
	switch (direction)
	{
	case MoveDirection::Up:
		if (result.y != 0) result.y -= 1;
		break;
	case MoveDirection::Down:
		if (result.y != MAP->mapSizeY) result.y += 1;
		break;
	case MoveDirection::Left:
		if (result.x != 0) result.x -= 1;
		break;
	case MoveDirection::Right:
		if (result.x != MAP->mapSizeX) result.x += 1;
		break;
	}
	return result;
}
void Player::ActionPick()
{
	POINT result = GetFrontTilePos();
	if (MAP->object[result.y][result.x] != nullptr)
	{
		MAP->object[result.y][result.x]->InteractionPick(1);
	}
}

int Player::GetFrame()
{
	static int frameNormal = 0;
	static int frameAction = 0;
	// 플레이어 프레임 조정

	switch (playerState) {
	case PlayerState::Normal:
		if (time > 0.2f)
		{
			time = 0.0f;
			frameNormal = 0;
		}
		else if (time > 0.1f)
		{
			time = 0.0f;
			++frameNormal;
			if (frameNormal >= 8 * 6) frameNormal -= 8 * 6;
		}

		if (direction == MoveDirection::Left || direction == MoveDirection::Right)
		{
			frameNormal %= 6;	// 6 = 플레이어 위, 아래 움직임 최대 프레임
		}
		else if (direction == MoveDirection::Up || direction == MoveDirection::Down)
		{
			frameNormal %= 8; // 8 = 플레이어 왼쪽, 오른쪽 최대 프레임
		}
		return frameNormal;
	case PlayerState::Pick:
		if (time > 0.1f)
		{
			time = 0.0f;
			++frameAction;
			if (frameAction == 5)
			{
				frameNormal = 0;
				frameAction = 0;
				actionCheck = false;
				playerState = PlayerState::Normal;
			}
		}
		return frameAction;		// 4 = 플레이어 곡괭이질 최대 프레임
	}
	return 0;
}

