#pragma once
#include "Singleton.h"

class GameDataManager : public Singleton<GameDataManager> {
private:
	POINTFLOAT playerPos;
	const string mapName[5];
	int mapNum;
public:
	GameDataManager() :
		playerPos{}, mapNum{ 0 },
		mapName
	{
		"Save/SaveMapData_Main.map",
		"Save/SaveMapData_Soil.map",
		"Save/SaveMapData_Ice.map",
		"Save/SaveMapData_Red.map",
		"Save/SaveMapData_End.map"
	} {};
	void Init() {}
public:

	inline void SetPlayerPos(POINTFLOAT pos) { playerPos = pos; }
	inline POINTFLOAT GetPlayerPos() { return playerPos; }

	void SetMapNum(int num) { mapNum = num; }
	int GetMapNum() { return mapNum; }
	const string GetMapString() { return mapName[mapNum]; }
	inline void Release() { this->ReleaseSingleton(); }
};