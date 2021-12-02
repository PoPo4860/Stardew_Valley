#pragma once
#include "Config.h"
#include "Singleton.h"
class ObjectPosManager : public Singleton<ObjectPosManager>
{
private:
	POINTFLOAT globalPos;
	int mapSizeX, mapSizeY;
	const int TILE_SIZE = 16;
public:
	inline void SetMapSize(int x, int y) 
	{ 
		mapSizeX = x * TILE_SIZE; 
		mapSizeY = y * TILE_SIZE;
	}
	inline void SetGlobalPos(POINTFLOAT playerPos)
	{
		if (WIN_SIZE_X > mapSizeX)
		{	// ���� ��ũ�Ⱑ ������ â ���� ���� ���
			globalPos.x = -((WIN_SIZE_X - mapSizeX) / 2);
		} 
		else
		{	// ���� ��ũ�Ⱑ ������ â���� Ŭ ��� 
			if ((WIN_SIZE_X / 2) <= playerPos.x <= mapSizeX - (WIN_SIZE_X / 2))
			{	// �÷��̾��� ��ġ�� ���ʰ� ������ ������ ����
				globalPos.x = playerPos.x - (WIN_SIZE_X / 2);
			}
			else if ((WIN_SIZE_X / 2) < playerPos.x)
			{	// �÷��̾��� ��ġ�� ���ʿ� ��������
				globalPos.x = 0;
			}
			else if (mapSizeX - (WIN_SIZE_X / 2) > playerPos.x)
			{	// �÷��̾��� ��ġ�� �����ʿ� ��������
				globalPos.x = mapSizeX - WIN_SIZE_X;
			}
		}
		if (WIN_SIZE_Y > mapSizeY)
		{	// ���� ��ũ�Ⱑ ������ â ���� ���� ���
			globalPos.y = -((WIN_SIZE_Y - mapSizeY) / 2);
		}
		else
		{	// ���� ��ũ�Ⱑ ������ â���� Ŭ ��� 
			if ((WIN_SIZE_Y / 2) <= playerPos.y && playerPos.y <= mapSizeY - (WIN_SIZE_Y / 2))
			{	// �÷��̾��� ��ġ�� ���� �Ʒ��� ������ ����
				globalPos.y = playerPos.y - (WIN_SIZE_Y / 2);
			}
			else if ((WIN_SIZE_Y / 2) > playerPos.y)
			{	// �÷��̾��� ��ġ�� ���� ��������
				globalPos.y = 0;
			}
			else if (mapSizeY - (WIN_SIZE_Y / 2) < playerPos.y)
			{	// �÷��̾��� ��ġ�� �Ʒ��� ��������
				globalPos.y = mapSizeY - WIN_SIZE_Y;
			}
		}
	}

	inline POINTFLOAT GetGlobalPos() { return globalPos; }
};