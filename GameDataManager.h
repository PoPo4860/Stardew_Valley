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

	inline void SetPlayerPos(POINTFLOAT pos) { playerPos = pos; }
	inline POINTFLOAT GetPlayerPos() { return playerPos; }

	inline void Release() { this->ReleaseSingleton(); }
};