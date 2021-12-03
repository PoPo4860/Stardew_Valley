#pragma once
#include "Config.h"
#include "MapInfo.h"

class Image;
class MapManager : public Singleton<MapManager>
{
private:
	MAP_INFO mapInfo;
	Image* selectDungeon;

public:
	void PrintMapRayer1(HDC hdc);
	void PrintMapRayer2(HDC hdc);
	void PrintMapRayer3(HDC hdc);
	const MAP_INFO* GetMap() { return &mapInfo; }
	void SetDungeonImage();
	void Load(int num);
};

