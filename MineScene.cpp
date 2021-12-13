#include "MineScene.h"
#include "CommonFunction.h"
#include "Image.h"
#include "Player.h"

HRESULT MineScene::Init()
{
    SetWindowSize(20, 10, WIN_SIZE_X * 3, WIN_SIZE_Y * 3);
    windowX = WIN_SIZE_X;
    windowY = WIN_SIZE_Y;
    MAP_MANAGER->Load(1);

    player = new Player;
    player->Init();
    COUT;
    return S_OK;
}

void MineScene::Update()
{
    player->Update();
    ITEM_MANAGER->Update();
    MAP_MANAGER->Update();
}

void MineScene::Render(HDC hdc)
{
    MAP_MANAGER->DrawMapLayer(hdc, 1);
    MAP_MANAGER->DrawMapLayer(hdc, 2);

    RENDER_MANAGER->PushObjectQueue(player);
    ITEM_MANAGER->PushObjectQueue();
    MAP_MANAGER->ObjectPush();
    RENDER_MANAGER->ObjectRender(hdc);
    MAP_MANAGER->DrawMapLayer(hdc, 3);
}

void MineScene::Release()
{
    SAFE_RELEASE(player);
}
