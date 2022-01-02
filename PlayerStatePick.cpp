#include "PlayerStatePick.h"
#include "Player.h"
#include "Image.h"
#include "Config.h"
HRESULT PlayerStatePick::Init()
{
	img = ImageManager::GetSingleton()->FindImage("Image/Player/Player_Pick_Action.bmp", 240, 192, 5, 4);
	return S_OK;
}

void PlayerStatePick::Update()
{
	frameTime += DELTA_TIME;
	if (frameTime > 0.1f)
	{
		frameTime -= 0.1f;
		++frame;
	}
	CheckAction();
}

void PlayerStatePick::Render(HDC hdc)
{
	img->Render(hdc,
		player->pos.x - GLOBAL_POS.x,
		player->pos.y - player->bodySize - GLOBAL_POS.y - 8,
		frame,
		player->playerDirection);
}

void PlayerStatePick::Release() {}

bool PlayerStatePick::CheckAction()
{
	if (frame >= 5)
	{
		frame = 0;
		frameTime = 0.0f;
		POINT result = player->GetFrontTilePos();
		if (MAP->object[result.y][result.x] != nullptr)
		{
			MAP->object[result.y][result.x]->InteractionPick(1);
		}
		player->playerState = PlayerState::Normal;
	}
	return false;
}

PlayerStatePick::PlayerStatePick(Player* player)
	:player{ player }, img{ nullptr }, frameTime{ 0.0f }, frame{ 0 }{};