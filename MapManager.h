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
public:
	MapManager();
	void Init() {}
	void Update();
	void ObjectPush();
	void Release();
public:
	void DrawMapLayer(HDC hdc, int LayerNum);
	// �� �׸���

	// �ʿ� �ִ� ������Ʈ ������Ʈ

	void ObjectClear();
	
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

