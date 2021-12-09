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

    //이미지 초기화

    ObjectPosManager::GetSingleton()->SetMapSize(MAP->mapSizeX, MAP->mapSizeY);
    player = new Player;
    player->Init();

    return S_OK;
}

void MineScene::Update()
{
    player->Update();
    MAP_MANAGER->Update();
}

void MineScene::Render(HDC hdc)
{
    MAP_MANAGER->DrawMapLayer(hdc, 1);
    MAP_MANAGER->DrawMapLayer(hdc, 2);
    MAP_MANAGER->pushQueue(player);
    MAP_MANAGER->ObjectRender(hdc);
    MAP_MANAGER->DrawMapLayer(hdc, 3);
}

void MineScene::Release()
{
    player->Release();
    delete player;
    player = nullptr;
}
