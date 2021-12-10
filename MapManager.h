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
	// �� �׸���

	void Release();
	// �ʿ� �ִ� ������Ʈ ������Ʈ

	void ObjectClear();
	
	void PushQueue(GameObject* obj) { objectQueue.push(obj); }
	// ������ ������Ʈ �߰�

	void ObjectRender(HDC hdc);
	// ������Ʈ ����
	
	
	const MAP_INFO* GetMap() { return &mapInfo; }
	void DeleteMapObject(POINT pos);
	// �ʿ� �ִ� ������Ʈ ����

	void Interaction(POINT pos);
	// ��ȣ�ۿ�

	void SetDungeonImage();
	void Load(int num);
	void CreateObject();
	// �ʿ� ������Ʈ ����
	
};

