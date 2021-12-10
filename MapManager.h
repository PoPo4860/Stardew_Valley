#pragma once
#include "Config.h"
#include "MapInfo.h"
#include "GameObject.h"
#include <algorithm>
#include <queue>
class Image;

struct compare
{
	bool operator()(GameObject* a, GameObject* b)
	{
		return a->GetPosY() > b->GetPosY();
	}
};
class MapManager : public Singleton<MapManager>
{
private:
	MAP_INFO mapInfo;
	Image* selectDungeon;
	priority_queue<GameObject*, vector<GameObject*>, compare> objectQueue;
public:
	MapManager();
	void DrawMapLayer(HDC hdc, int LayerNum);
	// �� �׸���

	void Update();
	// �ʿ� �ִ� ������Ʈ ������Ʈ
	void Release();
	
	void pushQueue(GameObject* obj) { objectQueue.push(obj); }
	// ������ ������Ʈ �߰�

	void ObjectRender(HDC hdc);
	// ������Ʈ ����
	
	
	const MAP_INFO* GetMap() { return &mapInfo; }
	void DeleteMapObject(int y, int x) { mapInfo.object[y][x] = nullptr; }
	// �ʿ� �ִ� ������Ʈ ����

	void SetDungeonImage();
	void Load(int num);
	void CreateObject();
	// �ʿ� ������Ʈ ����
	
};

