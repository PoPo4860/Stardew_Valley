#include "MineScene.h"
#include "CommonFunction.h"
#include "Image.h"
#include "Player.h"

HRESULT MineScene::Init()
{
    ImageManager::GetSingleton()->AddImage
    ("Image/Dungeon/Dungeon_Stone_Object.bmp", 192, 64, 12 , 4, true, RGB(255, 0, 255));
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
}

void MineScene::Render(HDC hdc)
{
    MAP_MANAGER->PrintMapRayer1(hdc);
    MAP_MANAGER->PrintMapRayer2(hdc);
    MapManager::GetSingleton()->pushQueue(player);
    MapManager::GetSingleton()->ObjectRender(hdc);
    //player->Render(hdc);
    
    MAP_MANAGER->PrintMapRayer3(hdc);
}

void MineScene::Release()
{

}
