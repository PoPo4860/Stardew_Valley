#pragma once
#include "GameEntity.h"
#include "Config.h"
#include "MapInfo.h"

class Player;
class Image;
class MineScene : public GameEntity
{
private:
	MAP_INFO mapInfo;
	Player* player;
	Image* selectDungeon;
	int mapPosX, mapPosY;
	int mapPrintX, mapPrintY;
public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;	// 오버로딩
	virtual void Release() override;
	MineScene()
		:mapInfo{},
		player{ nullptr }, 
		selectDungeon{ nullptr },
		mapPosX{ NULL }, mapPosY{ NULL },
		mapPrintX{ 20 }, mapPrintY{ 20 }
	{}
	virtual ~MineScene() = default;
	int Load(int num = 1);
};
