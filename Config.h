#pragma once
#include <Windows.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <map>
#include <iostream>
#include <string>

using namespace std;

#pragma comment(lib, "winmm.lib")

#define WIN_START_POS_X	400
#define WIN_START_POS_Y	100
#define WIN_SIZE_X	420			// 16 * 16
#define WIN_SIZE_Y	240			// 16 * 14
#define TILEMAPTOOL_SIZE_X	620
#define TILEMAPTOOL_SIZE_Y	330
#define PIXELMAP_SIZE_X	800
#define PIXELMAP_SIZE_Y	600
#define DEGREE_TO_RADIAN(x)		(x * PI / 180.0f)

#define SAFE_RELEASE(p)	{ if (p) { p->Release(); delete p; p = nullptr; } }
#define SAFE_DELETE(p)	{ if (p) { delete p; p = nullptr; } }

enum class MoveDir { Left, Right, Up, Down };

typedef struct ArgumentFuncPtr
{
	string sceneName;
	string loadingSceneName;
} ARGUMENT_PTR, *LPARGUMENT_PTR;

#include "TimerManager.h"
#include "ImageManager.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "GameDataManager.h"
#include "ObjectPosManager.h"

#define TIME TimerManager::GetSingleton()->GetDeltaTime() 
#define GLOBAL_POS ObjectPosManager::GetSingleton()->GetGlobalPos()
#define GLOBAL_POS_X GameDataManager::GetSingleton()->GetGlobalPosX()
#define GLOBAL_POS_Y GameDataManager::GetSingleton()->GetGlobalPosY()


extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
extern POINT g_ptMouse;
extern int windowX;
extern int windowY;