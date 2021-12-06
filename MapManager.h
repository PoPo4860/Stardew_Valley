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
	void DrawMapLayer(HDC hdc, int LayerNum);
	void CreateObject();
	void ObjectRender(HDC hdc);
	void pushQueue(GameObject* obj) { objectQueue.push(obj); }
	const MAP_INFO* GetMap() { return &mapInfo; }
	void SetDungeonImage();
	void Load(int num);
};

