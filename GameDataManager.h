#pragma once
#include "Singleton.h"

class GameDataManager : public Singleton<GameDataManager> {
private:
	POINTFLOAT globalPos;
	POINTFLOAT playerPos;
	int mapSizeX, mapSizeY;
public:
	GameDataManager() :
		globalPos{}, playerPos{}, mapSizeX{}, mapSizeY{}{};
	void Init() {}
public:
	inline POINTFLOAT GetGlobalPos() { return globalPos; }
	inline float GetGlobalPosX() { return globalPos.x; }
	inline float GetGlobalPosY() { return globalPos.y; }
	inline void SetGlobalPos(POINTFLOAT pos) 
	{ 
		pos.x *= -1;
		pos.y *= -1;
		globalPos = pos; 
	}
	inline void SetGlobalPosX(float pos) { globalPos.x = pos; }
	inline void SetGlobalPosY(float pos) { globalPos.y = pos; }

	inline void Release() { this->ReleaseSingleton(); }

};