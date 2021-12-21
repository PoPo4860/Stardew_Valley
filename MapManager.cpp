#include "MapManager.h"
#include "Image.h"
#include "SmallStone.h"


MapManager::MapManager() :
    mapInfo{}, selectDungeon{ nullptr }, ladderDownCheck{ false },  exit{}{}

void MapManager::Init()
{
}

void MapManager::DrawMapLayer(HDC hdc, int LayerNum)
{
    if (LayerNum == 1) LayerNum = 2;
    else if (LayerNum == 2) LayerNum = 1;
    else if (LayerNum == 3) LayerNum = 0;
    for (int y = 0; y < mapInfo.mapSizeY; ++y) {
        for (int x = 0; x < mapInfo.mapSizeX; ++x) {
            selectDungeon->Render(hdc,
                mapInfo.rect[y][x].left + (TILE_SIZE / 2) - GLOBAL_POS.x,
                mapInfo.rect[y][x].top + (TILE_SIZE / 2) - GLOBAL_POS.y,
                mapInfo.tileInfo[LayerNum][y][x].frameX,
                mapInfo.tileInfo[LayerNum][y][x].frameY);
        }
    }
}

void MapManager::CreateObject()
{
    int maxObject = 0;
    int minObject = 0;
    if (mapInfo.mapSizeY == 0)mapInfo.mapSizeY = 1;
    if (mapInfo.mapSizeX == 0)mapInfo.mapSizeX = 1;
    for (int y = 0; y < mapInfo.mapSizeY; ++y)
    {
        for (int x = 0; x < mapInfo.mapSizeX; ++x)
        {
            if (mapInfo.tileState[y][x] == Tile_State::Empty)
            {
                ++maxObject;
            }
        }
    }
    //맵을 순회하면서 오브젝트 설정이 가능한 최대갯수를 구함.

    maxObject /= 4;
    minObject = maxObject / 2;
    int objectCost = minObject + (rand() % (maxObject - minObject));
    // 현재 맵에 생성할 오브젝트의 비용을 설정함

    for (int count = 0; count < objectCost;)
    {
        int posX = rand() % mapInfo.mapSizeX;
        int posY = rand() % mapInfo.mapSizeY;

        if (mapInfo.tileState[posY][posX] == Tile_State::Empty && mapInfo.object[posY][posX] == nullptr)
        {   //  해당 타일이 비어있으며, 위칸에 사다리가 없을 경우 오브젝트 추가
            if (posY > 0 && mapInfo.tileState[posY - 1][posX] != Tile_State::LadderUp)
            {
                mapInfo.object[posY][posX] = new SmallStone(Stone_Object_Info::SmallStone_Lv1, posX, posY);
                ++count;
                if (/*rand() % (objectCost / 3) == 0*/true)
                {   // 생성될 스톤에 비례하여 탈출구 생성
                    POINT buffer;
                    buffer.x = posX;
                    buffer.y = posY;
                    exit.push_back(buffer);
                }
            }
        }
        if (count >= objectCost && exit.size() == 0)
        {   // 생성된 탈출구가 없다면 탈출구 생성
            POINT buffer;
            buffer.x = posX;
            buffer.y = posY;
            exit.push_back(buffer);
        }
    }
}

void MapManager::Update()
{
    for (int y = 0; y < mapInfo.mapSizeY; ++y)
    {
        for (int x = 0; x < mapInfo.mapSizeX; ++x)
        {
            if (mapInfo.tileState[y][x] == Tile_State::Empty && mapInfo.object[y][x] != nullptr)
            {
                mapInfo.object[y][x]->Update();
            }
        }
    }
}

void MapManager::Release()
{
    ObjectClear();
    ReleaseSingleton();
}

void MapManager::ObjectClear()
{
    for (int y = 0; y < mapInfo.mapSizeY; ++y)
    {
        for (int x = 0; x < mapInfo.mapSizeX; ++x)
        {
            if (mapInfo.tileState[y][x] == Tile_State::Empty && mapInfo.object[y][x] != nullptr)
            {
                mapInfo.object[y][x]->Release();
                mapInfo.object[y][x] = nullptr;
            }
        }
    }
}


void MapManager::DeleteMapObject(POINT pos)
{
    mapInfo.object[pos.y][pos.x] = nullptr;
    for (int i = 0; i < exit.size(); ++i)
    {
        if (exit[i].x == pos.x && exit[i].y == pos.y)
        {
            mapInfo.tileInfo[2][pos.y][pos.x].frameX = 13;
            mapInfo.tileInfo[2][pos.y][pos.x].frameY = 10;
            mapInfo.tileState[pos.y][pos.x] = Tile_State::LadderDown;
        }
    }
}

void MapManager::Interaction(POINT pos)
{
    if (mapInfo.tileState[pos.y][pos.x] == Tile_State::LadderDown)
    {
        ObjectClear();
        exit.clear();
        RENDER_MANAGER->VectorClear();
        ITEM_MANAGER->ItemVectorClear();
        SceneManager::GetSingleton()->ChangeScene("MineScene");
    }
}

void MapManager::SetDungeonImage()
{
    if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Soil)
    {
        selectDungeon = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Soil.bmp", 256, 288, 16, 18);
    }
    else if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Gray)
    {
        selectDungeon = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Soil.bmp", 256, 288, 16, 18);
    }
    else if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Ice)
    {        
        selectDungeon = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Soil.bmp", 256, 288, 16, 18);
    }
    else if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Ice2)
    {
        selectDungeon = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Soil.bmp", 256, 288, 16, 18);
    }
    else if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Red)
    {
        selectDungeon = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Soil.bmp", 256, 288, 16, 18);
    }
    else if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Sand)
    {
        selectDungeon = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Soil.bmp", 256, 288, 16, 18);
    }
    else if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Sand2)
    {
        selectDungeon = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Soil.bmp", 256, 288, 16, 18);
    }
    else if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Slime)
    {
        selectDungeon = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Soil.bmp", 256, 288, 16, 18);
    }
    else if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Soil)
    {
        selectDungeon = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Soil.bmp", 256, 288, 16, 18);
    }
    else if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Stone)
    {
        selectDungeon = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Soil.bmp", 256, 288, 16, 18);
    }
}

void MapManager::Load(int num)
{
    string loadFileName = "Save/SaveMapData_" + to_string(num) + ".map";

    HANDLE hFile = CreateFile(loadFileName.c_str(),
        GENERIC_READ,           // 읽기, 쓰기
        0, NULL,                // 공유, 보안 모드
        OPEN_EXISTING,          // 파일 만들거나 읽을 때 옵션
        FILE_ATTRIBUTE_NORMAL,  // 파일 속성(읽기 전용, 숨김 등등)
        NULL);

    DWORD readByte;
    if (ReadFile(
        hFile,
        &mapInfo,
        sizeof(MAP_INFO),
        &readByte, NULL) == false)
    {
        MessageBox(g_hWnd, "맵 데이터 로드에 실패했습니다.", "에러", MB_OK);
    }
    // 맵 로드

    SetDungeonImage();
    // 해당 맵에 알맞는 이미지 설정

    CreateObject();
    // 해당 맵에 알맞는 오브젝트 생성

    ObjectPosManager::GetSingleton()->SetMapSize(MAP->mapSizeX, MAP->mapSizeY);
    // 글로벌 포스에 맵 크기 지정

    CloseHandle(hFile);
}
