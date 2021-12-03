#pragma once
#include "Singleton.h"
class ObjectPosManager : public Singleton<ObjectPosManager>
{
private:
	POINTFLOAT globalPos;
	int mapSizeX, mapSizeY;
	int tileSize;
public:
	ObjectPosManager():
		globalPos{},
		tileSize{16},
		mapSizeX{ NULL }, mapSizeY{ NULL }
	{}

	inline void SetMapSize(int x, int y) 
	{ 
		mapSizeX = x * tileSize;
		mapSizeY = y * tileSize;
	}
	inline void SetGlobalPos(POINTFLOAT playerPos)
	{
		if (WIN_SIZE_X > mapSizeX)
		{	// 현재 맵크기가 윈도우 창 보다 작을 경우
			globalPos.x = -((WIN_SIZE_X - mapSizeX) / 2);
		} 
		else
		{	// 현재 맵크기가 윈도우 창보다 클 경우 
			if ((WIN_SIZE_X / 2) <= playerPos.x <= mapSizeX - (WIN_SIZE_X / 2))
			{	// 플레이어의 위치가 왼쪽과 오른쪽 사이일 때에
				globalPos.x = playerPos.x - (WIN_SIZE_X / 2);
			}
			else if ((WIN_SIZE_X / 2) < playerPos.x)
			{	// 플레이어의 위치가 왼쪽에 있을때에
				globalPos.x = 0;
			}
			else if (mapSizeX - (WIN_SIZE_X / 2) > playerPos.x)
			{	// 플레이어의 위치가 오른쪽에 있을때에
				globalPos.x = mapSizeX - WIN_SIZE_X;
			}
		}
		if (WIN_SIZE_Y > mapSizeY)
		{	// 현재 맵크기가 윈도우 창 보다 작을 경우
			globalPos.y = -((WIN_SIZE_Y - mapSizeY) / 2);
		}
		else
		{	// 현재 맵크기가 윈도우 창보다 클 경우 
			if ((WIN_SIZE_Y / 2) <= playerPos.y && playerPos.y <= mapSizeY - (WIN_SIZE_Y / 2))
			{	// 플레이어의 위치가 위과 아래쪽 사이일 때에
				globalPos.y = playerPos.y - (WIN_SIZE_Y / 2);
			}
			else if ((WIN_SIZE_Y / 2) > playerPos.y)
			{	// 플레이어의 위치가 위에 있을때에
				globalPos.y = 0;
			}
			else if (mapSizeY - (WIN_SIZE_Y / 2) < playerPos.y)
			{	// 플레이어의 위치가 아래에 있을때에
				globalPos.y = mapSizeY - WIN_SIZE_Y;
			}
		}
	}

	inline POINTFLOAT GetGlobalPos() { return globalPos; }
};