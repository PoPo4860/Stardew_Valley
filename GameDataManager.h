#pragma once
#include "Singleton.h"

class GameDataManager : public Singleton<GameDataManager> {
private:
	POINTFLOAT playerPos;
	int mapNum;
public:
	GameDataManager() :
		playerPos{}, mapNum{ 6 }{};
	void Init() {}
public:

	inline void SetPlayerPos(POINTFLOAT pos) { playerPos = pos; }
	inline POINTFLOAT GetPlayerPos() { return playerPos; }

	void SetMapNum(int num) { mapNum = num; }
	int GetMapNum() { return mapNum; }
	inline void Release() { this->ReleaseSingleton(); }
};