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
	// 맵 그리기

	void Update();
	// 맵에 있는 오브젝트 업데이트
	void Release();
	
	void pushQueue(GameObject* obj) { objectQueue.push(obj); }
	// 렌더할 오브젝트 추가

	void ObjectRender(HDC hdc);
	// 오브젝트 렌더
	
	
	const MAP_INFO* GetMap() { return &mapInfo; }
	void DeleteMapObject(int y, int x) { mapInfo.object[y][x] = nullptr; }
	// 맵에 있는 오브젝트 삭제

	void SetDungeonImage();
	void Load(int num);
	void CreateObject();
	// 맵에 오브젝트 생성
	
};

