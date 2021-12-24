#include "MineScene.h"
#include "CommonFunction.h"
#include "Image.h"
#include "Player.h"

HRESULT MineScene::Init()
{
    SetWindowSize(20, 10, WIN_SIZE_X * 3, WIN_SIZE_Y * 3);
    windowX = WIN_SIZE_X;
    windowY = WIN_SIZE_Y;
    MAP_MANAGER->Load(GAMEDATA_MANAGER->GetMapNum());
    player = new Player;
    player->Init();
    RENDER_MANAGER->PushObjectVector(player);

    return S_OK;
}

void MineScene::Update()
{
    if (INVEN_MANAVER->Uadate() == true)
    {   // 인벤토리가 열려있다면 바로 리턴
        return;
    }

    player->Update();
    ITEM_MANAGER->Update();
    MAP_MANAGER->Update();
}

void MineScene::Render(HDC hdc)
{
    MAP_MANAGER->DrawMapLayer(hdc, 1);
    MAP_MANAGER->DrawMapLayer(hdc, 2);
    RENDER_MANAGER->ObjectRender(hdc);
    MAP_MANAGER->DrawMapLayer(hdc, 3);
    INVEN_MANAVER->Render(hdc);
}

void MineScene::Release()
{
    SAFE_RELEASE(player);
    RENDER_MANAGER->VectorClear();
}
