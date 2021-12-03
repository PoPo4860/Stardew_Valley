#include "MapManager.h"
#include "Image.h"

void MapManager::PrintMapRayer1(HDC hdc)
{
    for (int y = 0; y < mapInfo.mapSizeY; ++y) {
        for (int x = 0; x < mapInfo.mapSizeX; ++x) {
            selectDungeon->Render(hdc,
                mapInfo.rect[y][x].left + (TILE_SIZE / 2) - GLOBAL_POS.x,
                mapInfo.rect[y][x].top + (TILE_SIZE / 2) - GLOBAL_POS.y,
                mapInfo.tileInfo[2][y][x].frameX,
                mapInfo.tileInfo[2][y][x].frameY);
        }
    }
}

void MapManager::PrintMapRayer2(HDC hdc)
{
    for (int y = 0; y < mapInfo.mapSizeY; ++y) {
        for (int x = 0; x < mapInfo.mapSizeX; ++x) {
            selectDungeon->Render(hdc,
                mapInfo.rect[y][x].left + (TILE_SIZE / 2) - GLOBAL_POS.x,
                mapInfo.rect[y][x].top + (TILE_SIZE / 2) - GLOBAL_POS.y,
                mapInfo.tileInfo[1][y][x].frameX,
                mapInfo.tileInfo[1][y][x].frameY);
        }
    }
}

void MapManager::PrintMapRayer3(HDC hdc)
{
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

void MapManager::SetDungeonImage()
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

void MapManager::Load(int num)
{
    string loadFileName = "Save/SaveMapData_" + to_string(num);
    loadFileName += ".map";

    HANDLE hFile = CreateFile(loadFileName.c_str(),
        GENERIC_READ,           // �б�, ����
        0, NULL,                // ����, ���� ���
        OPEN_EXISTING,          // ���� ����ų� ���� �� �ɼ�
        FILE_ATTRIBUTE_NORMAL,  // ���� �Ӽ�(�б� ����, ���� ���)
        NULL);
    //LPCVOID;

    // �б�
    DWORD readByte;
    if (ReadFile(
        hFile,
        &mapInfo,
        sizeof(MAP_INFO),
        &readByte, NULL) == false)
    {
        MessageBox(g_hWnd, "�� ������ �ε忡 �����߽��ϴ�.", "����", MB_OK);
    }

    CloseHandle(hFile);
}
