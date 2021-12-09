#pragma once
#include "Image.h"
#include <Windows.h>
#include <math.h>
#include "Config.h"
inline void SetWindowSize(int startX, int startY, int sizeX, int sizeY)
{
	// 원하는 윈도우 작업영역 설정
	RECT rc;
	rc.left = 0; rc.top = 0;
	rc.right = sizeX;	rc.bottom = sizeY;

	// 스타일이 포함된 실제 윈도우 크기 계산
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

	// 계산된 값으로 윈도우를 이동시키면서 크기도 함께 변환
	MoveWindow(g_hWnd, startX, startY,
		rc.right - rc.left, rc.bottom - rc.top, true);
}

inline POINT GetPosTile(POINTFLOAT pos, int mapSizeX = MAP->mapSizeX, int mapSizeY = MAP->mapSizeY) {
	int CountX = 0;
	CountX = ((int)pos.x / TILE_SIZE) % mapSizeX;
	if (CountX < 0) CountX = 0;
	if (CountX >= mapSizeX) CountX = mapSizeX - 1;

	int CountY = 0;
	CountY = ((int)pos.y / TILE_SIZE) % mapSizeY;
	if (CountY < 0) CountY = 0;
	if (CountY >= mapSizeY) CountY = mapSizeY - 1;

	
	POINT result;
	result.x = CountX;
	result.y = CountY;
	return result;
}

inline void SetRect(RECT* rect, POINTFLOAT pos,int bodySize)
{
	rect->left = pos.x - (bodySize / 2);
	rect->right = pos.x + (bodySize / 2);
	rect->top = pos.y - (bodySize / 2);
	rect->bottom = pos.y + (bodySize / 2);
}
