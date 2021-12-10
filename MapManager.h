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
	vector<POINT> exit;
public:
	MapManager();
	void Init() {}
	void Update();
public:
	void DrawMapLayer(HDC hdc, int LayerNum);
	// 맵 그리기

	void Release();
	// 맵에 있는 오브젝트 업데이트

	void ObjectClear();
	
	void PushQueue(GameObject* obj) { objectQueue.push(obj); }
	// 렌더할 오브젝트 추가

	void ObjectRender(HDC hdc);
	// 오브젝트 렌더
	
	
	const MAP_INFO* GetMap() { return &mapInfo; }
	void DeleteMapObject(POINT pos);
	// 맵에 있는 오브젝트 삭제

	void Interaction(POINT pos);
	// 상호작용

	void SetDungeonImage();
	void Load(int num);
	void CreateObject();
	// 맵에 오브젝트 생성
	
};

