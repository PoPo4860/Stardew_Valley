#pragma once
#include "GameObject.h"
class Player : public GameObject, public Character
{
private:
	POINTFLOAT mapPos;
	enum MoveDirection { Up = 0, Down = 1, Left = 2, Right = 3 };
	MoveDirection moveDirection;
	bool moveCheck = false;
	float frameX;
	float time;
public:
	Player();
	

	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();
	void Move(float posX, float posY);
	virtual ~Player() = default;
};
