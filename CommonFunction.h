#pragma once
#include "Image.h"
#include <Windows.h>
#include <math.h>
#include "Config.h"
inline void SetWindowSize(int startX, int startY, int sizeX, int sizeY)
{
	// ���ϴ� ������ �۾����� ����
	RECT rc;
	rc.left = 0; rc.top = 0;
	rc.right = sizeX;	rc.bottom = sizeY;

	// ��Ÿ���� ���Ե� ���� ������ ũ�� ���
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

	// ���� ������ �����츦 �̵���Ű�鼭 ũ�⵵ �Բ� ��ȯ
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
