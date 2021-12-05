#pragma once
#include "GameObject.h"
class Player : public GameObject
{
private:
	POINTFLOAT mapPos;
	enum MoveDirection: int { Up = 0, Down = 1, Left = 2, Right = 3 };
	MoveDirection moveDirection;
	bool moveCheck = false;
	float frameX;
	float time;
public:
	Player() :
		mapPos{},
		moveCheck{ false }, 
		frameX{ NULL },
		time{ NULL }, 
		moveDirection{ MoveDirection::Down }
	{};
	

	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();
	void Move(float posX, float posY);
	virtual ~Player() = default;
};
