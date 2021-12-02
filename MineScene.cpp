#include "MineScene.h"
#include "CommonFunction.h"
#include "Image.h"
#include "Player.h"

HRESULT MineScene::Init()
{
    Load();
    {
        if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Soil)
        {
            ImageManager::GetSingleton()->AddImage
            ("Image/Dungeon/Dungeon_Soil.bmp", 256, 288, 16, 18, true, RGB(255, 0, 255));
            selectDungeon = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Soil.bmp");
        }
        else if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Gray)
        {
            ImageManager::GetSingleton()->AddImage
            ("Image/Dungeon/Dungeon_Soil.bmp", 256, 288, 16, 18, true, RGB(255, 0, 255));
            selectDungeon = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Gray.bmp");
        }
        else if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Ice)
        {
            ImageManager::GetSingleton()->AddImage
            ("Image/Dungeon/Dungeon_Soil.bmp", 256, 288, 16, 18, true, RGB(255, 0, 255));
            selectDungeon = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Ice.bmp");
        }
        else if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Ice2)
        {
            ImageManager::GetSingleton()->AddImage
            ("Image/Dungeon/Dungeon_Soil.bmp", 256, 288, 16, 18, true, RGB(255, 0, 255));
            selectDungeon = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Ice2.bmp");
        }
        else if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Red)
        {
            ImageManager::GetSingleton()->AddImage
            ("Image/Dungeon/Dungeon_Soil.bmp", 256, 288, 16, 18, true, RGB(255, 0, 255));
            selectDungeon = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Red.bmp");
        }
        else if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Sand)
        {
            ImageManager::GetSingleton()->AddImage
            ("Image/Dungeon/Dungeon_Soil.bmp", 256, 288, 16, 18, true, RGB(255, 0, 255));
            selectDungeon = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Sand.bmp");
        }
        else if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Sand2)
        {
            ImageManager::GetSingleton()->AddImage
            ("Image/Dungeon/Dungeon_Soil.bmp", 256, 288, 16, 18, true, RGB(255, 0, 255));
            selectDungeon = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Sand2.bmp");
        }
        else if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Slime)
        {
            ImageManager::GetSingleton()->AddImage
            ("Image/Dungeon/Dungeon_Soil.bmp", 256, 288, 16, 18, true, RGB(255, 0, 255));
            selectDungeon = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Slime.bmp");
        }
        else if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Soil)
        {
            ImageManager::GetSingleton()->AddImage
            ("Image/Dungeon/Dungeon_Soil.bmp", 256, 288, 16, 18, true, RGB(255, 0, 255));
            selectDungeon = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Soil.bmp");
        }
        else if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Stone)
        {
            ImageManager::GetSingleton()->AddImage
            ("Image/Dungeon/Dungeon_Soil.bmp", 256, 288, 16, 18, true, RGB(255, 0, 255));
            selectDungeon = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Stone.bmp");
        }
    }
    //이미지 초기화
    ObjectPosManager::GetSingleton()->SetMapSize(mapInfo.mapSizeX, mapInfo.mapSizeY);
    player = new Player;
    player->Init();
    SetWindowSize(20, 10, WIN_SIZE_X * 3, WIN_SIZE_Y * 3);
    windowX = WIN_SIZE_X;
    windowY = WIN_SIZE_Y;

    if (mapInfo.mapSizeX * TILE_SIZE < 420)
        mapPosX = (WIN_SIZE_X - (mapInfo.mapSizeX * TILE_SIZE)) / 2;
    if (mapInfo.mapSizeY * TILE_SIZE < 240)
        mapPosY = (WIN_SIZE_Y - (mapInfo.mapSizeY * TILE_SIZE)) / 2;

    return S_OK;
}

void MineScene::Update()
{
    player->Update();
    //420 240
}

void MineScene::Render(HDC hdc)
{
    for (int z = 2; z > 0; --z) {
        for (int y = 0; y < mapInfo.mapSizeY; ++y) {
            for (int x = 0; x < mapInfo.mapSizeX; ++x) {
                selectDungeon->Render(hdc,
                    mapInfo.rect[y][x].left + (TILE_SIZE / 2) - GLOBAL_POS.x,
                    mapInfo.rect[y][x].top + (TILE_SIZE / 2) - GLOBAL_POS.y,
                    mapInfo.tileInfo[z][y][x].frameX,
                    mapInfo.tileInfo[z][y][x].frameY);
            }
        }
    }
    player->Render(hdc);
    for (int y = 0; y < mapInfo.mapSizeY; ++y) {
        for (int x = 0; x < mapInfo.mapSizeX; ++x) {
            selectDungeon->Render(hdc,
                mapInfo.rect[y][x].left + (TILE_SIZE / 2) - GLOBAL_POS.x,
                mapInfo.rect[y][x].top + (TILE_SIZE / 2) - GLOBAL_POS.y,
                mapInfo.tileInfo[0][y][x].frameX,
                mapInfo.tileInfo[0][y][x].frameY);
        }
    }
}

void MineScene::Release()
{

}

int MineScene::Load(int num)
{
    //int loadIndex;
    //cout << "로드할 맵의 번호를 입력하여 주십시오. : ";
    //cin >> loadIndex;
    string loadFileName = "Save/SaveMapData_" + to_string(num);
    loadFileName += ".map";

    HANDLE hFile = CreateFile(loadFileName.c_str(),
        GENERIC_READ,           // 읽기, 쓰기
        0, NULL,                // 공유, 보안 모드
        OPEN_EXISTING,          // 파일 만들거나 읽을 때 옵션
        FILE_ATTRIBUTE_NORMAL,  // 파일 속성(읽기 전용, 숨김 등등)
        NULL);
    //LPCVOID;

    // 읽기
    DWORD readByte;
    if (ReadFile(
        hFile,
        &mapInfo,
        sizeof(MAP_INFO),
        &readByte, NULL) == false)
    {
        MessageBox(g_hWnd, "맵 데이터 로드에 실패했습니다.", "에러", MB_OK);
    }

    CloseHandle(hFile);
    return 1;
}
