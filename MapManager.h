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
	// �� �׸���

	void ClearObject();
	
	
	const MAP_INFO* GetMap() { return &mapInfo; }
	
	// �ʿ� �ִ� ������Ʈ ����
	void DeleteMapObject(POINT pos);

	void Interaction(POINT pos);
	// ��ȣ�ۿ�

	void SetDungeonImage();
	void Load(int num);
	void CreateObject();
	// �ʿ� ������Ʈ ����
	
};

