#pragma once
#include "Singleton.h"

class GameDataManager : public Singleton<GameDataManager> {
private:
	POINTFLOAT playerPos;
public:
	GameDataManager() :
		 playerPos{}{};
	void Init() {}
public:
	//inline POINTFLOAT GetGlobalPos() { return globalPos; }
	//inline float GetGlobalPosX() { return globalPos.x; }
	//inline float GetGlobalPosY() { return globalPos.y; }
	//inline void SetGlobalPos(POINTFLOAT pos) 
	//{ 
	//	pos.x *= -1;
	//	pos.y *= -1;
	//	globalPos = pos; 
	//}
	//inline void SetGlobalPosX(float pos) { globalPos.x = pos; }
	//inline void SetGlobalPosY(float pos) { globalPos.y = pos; }

	inline void SetPlayerPos(POINTFLOAT pos) { playerPos = pos; }
	inline POINTFLOAT GetPlayerPos() { return playerPos; }

	inline void Release() { this->ReleaseSingleton(); }
};