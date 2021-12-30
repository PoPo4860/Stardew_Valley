#pragma once
#include "GameEntity.h"
class Player;
class Image;
class PlayerStateMove : public GameEntity
{
private:
	Player* player;
	Image* img;
	float frameTime;
	int frame;
	void Move(float posX, float posY);
	void MovePlayer();

protected:
public:
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();
	bool CheckAction();
	PlayerStateMove(Player* player);
	virtual ~PlayerStateMove() = default;

public:
};

