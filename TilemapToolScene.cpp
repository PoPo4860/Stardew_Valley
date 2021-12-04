#include "TilemapToolScene.h"
#include "Image.h"
#include "CommonFunction.h"

HRESULT TilemapToolScene::Init()
{
    SetWindowSize(20, 10, TILEMAPTOOL_SIZE_X*3, TILEMAPTOOL_SIZE_Y*3);
    windowX = TILEMAPTOOL_SIZE_X;
    windowY = TILEMAPTOOL_SIZE_Y;
    {
        ImageManager::GetSingleton()->AddImage
        ("Image/Dungeon/Dungeon_Gray.bmp", 256, 288, 16, 18, true, RGB(255, 0, 255));
        dungeonGray = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Gray.bmp");
        ImageManager::GetSingleton()->AddImage
        ("Image/Dungeon/Dungeon_Ice.bmp", 256, 288, 16, 18, true, RGB(255, 0, 255));
        dungeonIce = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Ice.bmp");
        ImageManager::GetSingleton()->AddImage
        ("Image/Dungeon/Dungeon_Ice2.bmp", 256, 288, 16, 18, true, RGB(255, 0, 255));
        dungeonIce2 = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Ice2.bmp");
        ImageManager::GetSingleton()->AddImage
        ("Image/Dungeon/Dungeon_Red.bmp", 256, 288, 16, 18, true, RGB(255, 0, 255));
        dungeonRed = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Red.bmp");
        ImageManager::GetSingleton()->AddImage
        ("Image/Dungeon/Dungeon_Sand.bmp", 256, 288, 16, 18, true, RGB(255, 0, 255));
        dungeonSand = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Sand.bmp");
        ImageManager::GetSingleton()->AddImage
        ("Image/Dungeon/Dungeon_Sand2.bmp", 256, 288, 16, 18, true, RGB(255, 0, 255));
        dungeonSand2 = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Sand2.bmp");
        ImageManager::GetSingleton()->AddImage
        ("Image/Dungeon/Dungeon_Slime.bmp", 256, 288, 16, 18, true, RGB(255, 0, 255));
        dungeonSlime = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Slime.bmp");
        ImageManager::GetSingleton()->AddImage
        ("Image/Dungeon/Dungeon_Soil.bmp", 256, 288, 16, 18, true, RGB(255, 0, 255));
        dungeonSoil = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Soil.bmp");
        ImageManager::GetSingleton()->AddImage
        ("Image/Dungeon/Dungeon_Stone.bmp", 256, 288, 16, 18, true, RGB(255, 0, 255));
        dungeonStone = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Stone.bmp");
        ImageManager::GetSingleton()->AddImage
        ("Image/Dungeon/TileMapTool_Layer.bmp", 64, 64, 4, 1);
        layerNumImage = ImageManager::GetSingleton()->FindImage("Image/Dungeon/TileMapTool_Layer.bmp");
        ImageManager::GetSingleton()->AddImage
        ("Image/Dungeon/TileMapTool_LayerMode.bmp", 64, 64, 4, 1);
        layerModeImage = ImageManager::GetSingleton()->FindImage("Image/Dungeon/TileMapTool_LayerMode.bmp");
        ImageManager::GetSingleton()->AddImage
        ("Image/Dungeon/TileMapTool_TileState.bmp", 80, 80, 5, 1);
        tileStateImage = ImageManager::GetSingleton()->FindImage("Image/Dungeon/TileMapTool_TileState.bmp");
    }
    selectDungeon = dungeonSoil;
    // ���� ��� ���� ���� �ʱ�ȭ
    for (int y = 0; y < 256; ++y)  // y��
    {
        for (int x = 0; x < 256; ++x)  // x�� 
        {
            SetRect(&(mapInfo.rect[y][x]),
                x * (TILE_SIZE),
                y * (TILE_SIZE),
                x * (TILE_SIZE) + (TILE_SIZE),
                y * (TILE_SIZE) + (TILE_SIZE));
            mapInfo.tileState[y][x] = tileState;
            mapInfo.tileInfo[0][y][x].frameX = 0;
            mapInfo.tileInfo[0][y][x].frameY = 1;
            mapInfo.tileInfo[1][y][x].frameX = 0;
            mapInfo.tileInfo[1][y][x].frameY = 1;
            mapInfo.tileInfo[2][y][x].frameX = 0;
            mapInfo.tileInfo[2][y][x].frameY = 1;
        }
    }

    // ���õ� Ÿ��
    selectedSampleTile.frameX = 0;
    selectedSampleTile.frameY = 0;
    return S_OK;
}

void TilemapToolScene::Update()
{
    mouse = g_ptMouse;
    RECT rect;
    GetClientRect(g_hWnd, &rect);
    POINT view;
    view.x = rect.right - rect.left;
    view.y = rect.bottom - rect.top;
    if (view.x != TILEMAPTOOL_SIZE_X || view.y != TILEMAPTOOL_SIZE_Y) 
    {
        view.x /= TILEMAPTOOL_SIZE_X;
        view.y /= TILEMAPTOOL_SIZE_Y;
        mouse.x /= view.x;
        mouse.y /= view.y;
    }

    
    // Ÿ�ϸ��� ���Ű
    {
        if (KeyManager::GetSingleton()->IsOnceKeyDown('1'))             //==========================
            layerNum = 0;                                               //
        else if (KeyManager::GetSingleton()->IsOnceKeyDown('2'))        //
            layerNum = 1;                                               //  ���̾� ����
        else if (KeyManager::GetSingleton()->IsOnceKeyDown('3'))        //
            layerNum = 2;                                               //
        else if (KeyManager::GetSingleton()->IsOnceKeyDown('4'))        //
            layerNum = 3;                                               //
        if (KeyManager::GetSingleton()->IsOnceKeyDown('Z'))             //==========================
        {                                                               //
            if (tileState == Tile_State::Empty)                         //
                tileState = Tile_State::LadderDown;                     //
            else if (tileState == Tile_State::LadderDown)               //
                tileState = Tile_State::LadderUp;                       //
            else if (tileState == Tile_State::LadderUp)                 // Ÿ�� ���� ����
                tileState = Tile_State::Light;                          //
            else if (tileState == Tile_State::Light)                    //
                tileState = Tile_State::Wall;                           //
            else if (tileState == Tile_State::Wall)                     //
                tileState = Tile_State::Empty;                          //
        }                                                               //
        else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_UP))      //==========================
        {                                                               //
            --mapPosY;                                                  //
            if (mapPosY < 0) mapPosY = 0;                               //
            cout << "mapPosX : " << mapPosX << " mapPosY : " << mapPosY << "\n";
        }                                                               //
        else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_DOWN))    //
        {                                                               //
            ++mapPosY;                                                  //
            cout << "mapPosX : " << mapPosX << " mapPosY : " << mapPosY << "\n";
        }                                                               //
        else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RIGHT))   // �������� ��ũ�� ����
        {                                                               //
            ++mapPosX;                                                  //
            cout << "mapPosX : " << mapPosX << " mapPosY : " << mapPosY << "\n";
        }                                                               //
        else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LEFT))    //
        {                                                               //
            --mapPosX;                                                  //
            if (mapPosX < 0) mapPosX = 0;                               //
            cout << "mapPosX : " << mapPosX << " mapPosY : " << mapPosY << "\n";
        }                                                               //==========================
        else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_NUMPAD6)) //
        {                                                               //
            ++mapInfo.mapSizeX;                                         // 
            cout << "mapSizeX : " << mapInfo.mapSizeX << " mapSizeY : " << mapInfo.mapSizeY << "\n";
        }                                                               //
        else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_NUMPAD4)) // 
        {                                                               //
            --mapInfo.mapSizeX;                                         //
            cout << "mapSizeX : " << mapInfo.mapSizeX << " mapSizeY : " << mapInfo.mapSizeY << "\n";
        }                                                               //
        else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_NUMPAD8)) // 
        {                                                               //
            --mapInfo.mapSizeY;                                         // ���� ��ũ�� ����
            cout << "mapSizeX : " << mapInfo.mapSizeX << " mapSizeY : " << mapInfo.mapSizeY << "\n";
        }                                                               //
        else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_NUMPAD5)) // 
        {                                                               //
            ++mapInfo.mapSizeY;                                         // 
            cout << "mapSizeX : " << mapInfo.mapSizeX << " mapSizeY : " << mapInfo.mapSizeY << "\n";
        }                                                               //==========================
        else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_NUMPAD3)) //
        {                                                               //
            if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Gray)    //
            {                                                           //
                selectDungeon = dungeonIce;                             //
                mapInfo.dungeonTiles = Dungeon_Tiles::Dungeon_Ice;      //
            }                                                           //
            else if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Ice)//
            {                                                           //
                selectDungeon = dungeonIce2;                            //
                mapInfo.dungeonTiles = Dungeon_Tiles::Dungeon_Ice2;     //  ���ÿ��� ����
            }                                                           //
            else if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Ice2)
            {                                                           //
                selectDungeon = dungeonRed;                             //
                mapInfo.dungeonTiles = Dungeon_Tiles::Dungeon_Red;      //
            }                                                           //
            else if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Red)//
            {                                                           //
                selectDungeon = dungeonSand;                            //
                mapInfo.dungeonTiles = Dungeon_Tiles::Dungeon_Sand;     //
            }                                                           //
            else if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Sand)//
            {                                                           //
                selectDungeon = dungeonSand2;                           //
                mapInfo.dungeonTiles = Dungeon_Tiles::Dungeon_Sand2;    //
            }                                                           //
            else if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Sand2)
            {                                                           //
                selectDungeon = dungeonSlime;                           //
                mapInfo.dungeonTiles = Dungeon_Tiles::Dungeon_Slime;    //
            }                                                           //
            else if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Slime)
            {                                                           //
                selectDungeon = dungeonSoil;                            //
                mapInfo.dungeonTiles = Dungeon_Tiles::Dungeon_Soil;     //
            }                                                           //
            else if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Soil)
            {                                                           //
                selectDungeon = dungeonStone;                           //
                mapInfo.dungeonTiles = Dungeon_Tiles::Dungeon_Stone;    //
            }                                                           //
            else if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Stone)
            {                                                           //
                selectDungeon = dungeonGray;                            //
                mapInfo.dungeonTiles = Dungeon_Tiles::Dungeon_Gray;     //=========================
            }                                                           //
        }                                                               //
        else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_NUMPAD1)) //
        {                                                               //
            mapInfoTemp = mapInfo;                                      //
            for (int y = 0; y < mapInfo.mapSizeY; ++y)                  //  ���̾� 1ĭ�� �б�
            {                                                           //
                for (int x = 0; x < mapInfo.mapSizeX; ++x)              //
                {                                                       //
                    mapInfo.tileInfo[1][y][x].frameX = mapInfoTemp.tileInfo[0][y][x].frameX;
                    mapInfo.tileInfo[1][y][x].frameY = mapInfoTemp.tileInfo[0][y][x].frameY;
                    mapInfo.tileInfo[2][y][x].frameX = mapInfoTemp.tileInfo[1][y][x].frameX;
                    mapInfo.tileInfo[2][y][x].frameY = mapInfoTemp.tileInfo[1][y][x].frameY;
                    mapInfo.tileInfo[0][y][x].frameX = mapInfoTemp.tileInfo[2][y][x].frameX;
                    mapInfo.tileInfo[0][y][x].frameY = mapInfoTemp.tileInfo[2][y][x].frameY;
                }
            }
        }
        else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_NUMPAD2))
        {
            ++layerMode;
            if (layerMode == 4) layerMode = 0;
        }

        mapPrintX = mapPosX + 20;
        if (mapInfo.mapSizeX < mapPrintX)
            mapPrintX = mapInfo.mapSizeX;
        mapPrintY = mapPosY + 20;
        if (mapInfo.mapSizeY < mapPrintY)
            mapPrintY = mapInfo.mapSizeY;
    }
    
    // ������ ��� ���� ���� �ʱ�ȭ
    for (int y = 0; y < 18; ++y)    // y��
    {
        for (int x = 0; x < 16; ++x)    // x��
        {
            SetRect(&(sampleTileInfo[y][x].rc),
                TILEMAPTOOL_SIZE_X - selectDungeon->GetWidth() + x * TILE_SIZE,
                y * TILE_SIZE,
                TILEMAPTOOL_SIZE_X - selectDungeon->GetWidth() + x * TILE_SIZE + TILE_SIZE,
                y * TILE_SIZE + TILE_SIZE);

            sampleTileInfo[y][x].frameX = x;
            sampleTileInfo[y][x].frameY = y;
        }
    }
    // ���ÿ������� ������ ����
    RECT sampleArea;
    sampleArea.left = TILEMAPTOOL_SIZE_X - selectDungeon->GetWidth();
    sampleArea.right = TILEMAPTOOL_SIZE_X;
    sampleArea.top = 0;
    sampleArea.bottom = selectDungeon->GetHeight();

    if (PtInRect(&(sampleArea), mouse))
    {
        if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON)) {
            int posX = mouse.x - sampleArea.left;
            selectedSampleTile.frameX = sampleTileWidth = posX / TILE_SIZE;
            int posY = mouse.y - sampleArea.top;
            selectedSampleTile.frameY = sampleTileHeight = posY / TILE_SIZE;
        }

        if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON)) {
            int posX = mouse.x - sampleArea.left;
            sampleTileWidth -= posX / TILE_SIZE;
            int posY = mouse.y - sampleArea.top;
            sampleTileHeight -= posY / TILE_SIZE;

            if (sampleTileWidth < 0) sampleTileWidth *= -1;
            if (sampleTileHeight < 0) sampleTileHeight *= -1;
        }
    }

    // ���ο������� ���õ� ���� ������ ����
    if (layerNum != 3)
    {
        for (int y = mapPosY; y < mapPosY + 20; ++y) {
            for (int x = mapPosX; x < mapPosX + 20; ++x) {
                RECT rc = mapInfo.rect[y][x];
                rc.left -= (mapPosX * TILE_SIZE); rc.right -= (mapPosX * TILE_SIZE);
                rc.top -= (mapPosY * TILE_SIZE); rc.bottom -= (mapPosY * TILE_SIZE);
                if (PtInRect(&rc, mouse)) {
                    if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON)) {
                        for (int height = 0; height <= sampleTileHeight; ++height)
                        {
                            if (mapPosY + height >= mapPrintY) break;
                            for (int width = 0; width <= sampleTileWidth; ++width)
                            {
                                if (mapPosX + height >= mapPrintX) break;
                                mapInfo.tileInfo[layerNum][y + height][x + width].frameX = selectedSampleTile.frameX + width;
                                mapInfo.tileInfo[layerNum][y + height][x + width].frameY = selectedSampleTile.frameY + height;
                            }
                        }
                    }
                }
            }
        }
    }
    else
    {
        for (int y = mapPosY; y < mapPosY + 20; ++y) {
            for (int x = mapPosX; x < mapPosX + 20; ++x) {
                RECT rc = mapInfo.rect[y][x];
                rc.left -= (mapPosX * TILE_SIZE); rc.right -= (mapPosX * TILE_SIZE);
                rc.top -= (mapPosY * TILE_SIZE); rc.bottom -= (mapPosY * TILE_SIZE);
                if (PtInRect(&rc, mouse)) {
                    if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON)) {
                        mapInfo.tileState[y][x] = tileState;
                    }
                }
            }
        }
    }

    // ���̺�
    if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_NUMPAD7))
        Save();
    // �ε�
    if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_NUMPAD9))
        Load();
}

void TilemapToolScene::Render(HDC hdc)
{
    // ���� ����
    if (layerMode == 0) // ���̾� ��尡 ǥ�ػ����϶�
    {
        for (int z = 2; z > -1; --z) {
            for (int y = mapPosY; y < mapPrintY; ++y) {
                for (int x = mapPosX; x < mapPrintX; ++x) {
                    selectDungeon->Render(hdc,
                        mapInfo.rect[y][x].left + (TILE_SIZE / 2) - (mapPosX * TILE_SIZE),
                        mapInfo.rect[y][x].top + (TILE_SIZE / 2) - (mapPosY * TILE_SIZE),
                        mapInfo.tileInfo[z][y][x].frameX,
                        mapInfo.tileInfo[z][y][x].frameY);
                }
            }
        }
    }
    else // ���̾� ��尡 �� �ش� ���̾ ����ϰ� ���� ����
    {
        for (int y = mapPosY; y < mapPrintY; ++y) {
            for (int x = mapPosX; x < mapPrintX; ++x) {
                selectDungeon->Render(hdc,
                    mapInfo.rect[y][x].left + (TILE_SIZE / 2) - (mapPosX * TILE_SIZE),
                    mapInfo.rect[y][x].top + (TILE_SIZE / 2) - (mapPosY * TILE_SIZE),
                    mapInfo.tileInfo[layerMode - 1][y][x].frameX,
                    mapInfo.tileInfo[layerMode - 1][y][x].frameY);
            }
        }
    }

    if (layerNum == 3)
    {
        for (int y = mapPosY; y < mapPrintY; ++y) {
            for (int x = mapPosX; x < mapPrintX; ++x) {
                if (mapInfo.tileState[y][x] == Tile_State::Empty)
                    pen = (HPEN)CreateSolidBrush(RGB(20, 20, 20));
                if (mapInfo.tileState[y][x] == Tile_State::Light)
                    pen = (HPEN)CreateSolidBrush(RGB(239, 228, 176));
                if (mapInfo.tileState[y][x] == Tile_State::LadderDown)
                    pen = (HPEN)CreateSolidBrush(RGB(128, 64, 0));
                if (mapInfo.tileState[y][x] == Tile_State::LadderUp)
                    pen = (HPEN)CreateSolidBrush(RGB(255, 128, 64));
                if (mapInfo.tileState[y][x] == Tile_State::Wall)
                    pen = (HPEN)CreateSolidBrush(RGB(0, 128, 64));
                oPen = (HPEN)SelectObject(hdc, pen);
                Rectangle(hdc,
                    mapInfo.rect[y][x].left - (mapPosX * TILE_SIZE),
                    mapInfo.rect[y][x].top - (mapPosY * TILE_SIZE),
                    mapInfo.rect[y][x].right - (mapPosX * TILE_SIZE),
                    mapInfo.rect[y][x].bottom - (mapPosY * TILE_SIZE));
                SelectObject(hdc, oPen);
                DeleteObject(pen);
            }
        }
    }

    // ���̾� ����
    layerNumImage->Render(hdc, TILEMAPTOOL_SIZE_X - 265, TILEMAPTOOL_SIZE_Y - 150, layerNum, 0);
    if (layerMode == 0)
        layerModeImage->Render(hdc, TILEMAPTOOL_SIZE_X - 281, TILEMAPTOOL_SIZE_Y - 150, 3, 0);
    else
        layerModeImage->Render(hdc, TILEMAPTOOL_SIZE_X - 281, TILEMAPTOOL_SIZE_Y - 150, layerMode - 1, 0);
    if (tileState == Tile_State::Empty)
        tileStateImage->Render(hdc, TILEMAPTOOL_SIZE_X - 265, TILEMAPTOOL_SIZE_Y - 222, 0, 0);
    else if (tileState == Tile_State::LadderDown)
        tileStateImage->Render(hdc, TILEMAPTOOL_SIZE_X - 265, TILEMAPTOOL_SIZE_Y - 222, 1, 0);
    else if (tileState == Tile_State::LadderUp)
        tileStateImage->Render(hdc, TILEMAPTOOL_SIZE_X - 265, TILEMAPTOOL_SIZE_Y - 222, 2, 0);
    else if (tileState == Tile_State::Light)
        tileStateImage->Render(hdc, TILEMAPTOOL_SIZE_X - 265, TILEMAPTOOL_SIZE_Y - 222, 3, 0);
    else if (tileState == Tile_State::Wall)
        tileStateImage->Render(hdc, TILEMAPTOOL_SIZE_X - 265, TILEMAPTOOL_SIZE_Y - 222, 4, 0);


    // ���õ� Ÿ��
    selectDungeon->Render(
        hdc,
        TILEMAPTOOL_SIZE_X - 265,
        TILEMAPTOOL_SIZE_Y - 100,
        selectedSampleTile.frameX,
        selectedSampleTile.frameY,
        0,
        0);

    // ������� ���� ����
    selectDungeon->Render(
        hdc,
        TILEMAPTOOL_SIZE_X - selectDungeon->GetWidth() / 2,
        selectDungeon->GetHeight() / 2);
}

void TilemapToolScene::Release()
{
}

void TilemapToolScene::Save()
{
    int saveIndex;
    cout << "���̺��� ���� ��ȣ�� �Է��Ͽ� �ֽʽÿ�. : ";
    cin >> saveIndex;
    string saveFileName = "Save/saveMapData_" + to_string(saveIndex);
    saveFileName += ".map";

    HANDLE hFile = CreateFile(saveFileName.c_str(),
        GENERIC_WRITE,          // �б�, ����
        0, NULL,                // ����, ���� ���
        CREATE_ALWAYS,          // ���� ����ų� ���� �� �ɼ�
        FILE_ATTRIBUTE_NORMAL,  // ���� �Ӽ�(�б� ����, ���� ���)
        NULL);

    // ����
    DWORD byteSize = sizeof(MAP_INFO);
    //mapInfo2.dungeonTiles = mapInfo.dungeonTiles;
    //mapInfo2.mapSizeX = mapInfo.mapSizeX;
    //mapInfo2.mapSizeY = mapInfo.mapSizeY;
    //mapInfo2.dungeonTiles = mapInfo.dungeonTiles;
    //for (int z = 0; z < 3; ++z) {
    //    for (int y = 0; y < mapInfo.mapSizeY; ++y) {
    //        for (int x = 0; x < mapInfo.mapSizeX; ++x) {
    //            mapInfo2.rect[y][x] = mapInfo.rect[y][x];
    //            mapInfo2.tileInfo[z][y][x] = mapInfo.tileInfo[z][y][x];
    //            mapInfo2.tileState[y][x] = mapInfo.tileState[y][x];
    //        }
    //    }
    //}
    DWORD writtenByte;
    if (WriteFile(hFile,                            // ���� �ڵ�
        &mapInfo,                                   // �޸� �����ּ�
        sizeof(MAP_INFO),                           // �޸� ũ��
        &writtenByte,                               // ���� ������ ���� �뷮
        NULL) == false)                             // ???
    {
        cout << "���� ���� \n";
    }
    CloseHandle(hFile);
}

void TilemapToolScene::Load()
{
    int loadIndex;
    cout << "�ε��� ���� ��ȣ�� �Է��Ͽ� �ֽʽÿ�. : ";
    cin >> loadIndex;
    string loadFileName = "Save/SaveMapData_" + to_string(loadIndex);
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
