#include "ImageManager.h"
#include "KeyManager.h"
#include "TimerManager.h"
#include "Player.h"
#include "Image.h"
HRESULT Player::Init()
{
	ImageManager::GetSingleton()->AddImage
	("Image/Player.bmp", 10, 10, 1, 1, true, RGB(255, 0, 255));
	img = ImageManager::GetSingleton()->FindImage("Image/Player.bmp");
	pos.x = 300.0f;
	pos.y = 50.0f;
	moveSpeed = 150.0f;
	return S_OK;
}

void Player::Update()
{
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_UP))
		pos.y -= moveSpeed * TIME;
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN))
		pos.y += moveSpeed * TIME;
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
		pos.x -= moveSpeed * TIME;
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
		pos.x += moveSpeed * TIME;
	ObjectPosManager::GetSingleton()->SetGlobalPos(pos);
}

void Player::Render(HDC hdc)
{
	//img->Render(hdc, pos.x, pos.y, 0, 0);
	img->Render(hdc, pos.x - GLOBAL_POS.x, pos.y - GLOBAL_POS.y, 0, 0);
}

void Player::Release()
{
}
