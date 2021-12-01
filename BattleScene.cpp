#include "BattleScene.h"

HRESULT BattleScene::Init()
{
    return S_OK;
}

void BattleScene::Update()
{

}

void BattleScene::Render(HDC hdc)
{
}

void BattleScene::Release()
{

}

int BattleScene::Load(int num)
{
    int loadIndex;
    cout << "로드할 맵의 번호를 입력하여 주십시오. : ";
    cin >> loadIndex;
    string loadFileName = "Save/SaveMapData_" + to_string(loadIndex);
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
