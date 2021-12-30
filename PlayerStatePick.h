#pragma once
#include "GameEntity.h"
class Player;
class Image;
class PlayerStatePick : public GameEntity
{
private:
	const Player* player;
	Image* img;
	float frameTime;
	int frame;
protected:
public:
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();
	bool CheckAction();
	PlayerStatePick(const Player* player);
	virtual ~PlayerStatePick() = default;

public:

};

