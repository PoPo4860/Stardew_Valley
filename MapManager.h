#pragma once
#include "Config.h"
#include "MapInfo.h"
#include "GameObject.h"

class Image;
class MapManager : public Singleton<MapManager>
{
private:
	MAP_INFO mapInfo;
	Image* selectDungeon;
	vector<POINT> exit;
	bool ladderDownCheck;
public:
	MapManager();
	void Init();
	void Update();
	void Release();
public:
	void DrawMapLayer(HDC hdc, int LayerNum);
	// 맵 그리기

	void ClearObject();
	
	
	const MAP_INFO* GetMap() { return &mapInfo; }
	
	// 맵에 있는 오브젝트 삭제
	void DeleteMapObject(POINT pos);

	void Interaction(POINT pos);
	// 상호작용

	void SetDungeonImage();
	void Load(int num);
	void CreateObject();
	// 맵에 오브젝트 생성
	
};

