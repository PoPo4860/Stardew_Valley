#pragma once
#include "Config.h"
#include "MapInfo.h"
#include "GameObject.h"
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
	void PrintMapRayer1(HDC hdc);
	void PrintMapRayer2(HDC hdc);
	void PrintMapRayer3(HDC hdc);
	void CreateObject();
	void ObjectRender(HDC hdc);
	void pushQueue(GameObject* obj) { objectQueue.push(obj); }
	const MAP_INFO* GetMap() { return &mapInfo; }
	void SetDungeonImage();
	void Load(int num);
};

