#pragma once
#include "GameEntity.h"
class Player;
class Image;
class PlayerStatePick : public GameEntity
{
private:
	Player* player;
	Image* img;
	float frameTime;
	int frame;
protected:
public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	bool CheckAction();
	PlayerStatePick(Player* player);
	virtual ~PlayerStatePick() = default;

public:

};

