#pragma once
#include "GameObject.h"
class Player : public GameObject
{
private:
	POINTFLOAT mapPos;
public:
	Player()
		:mapPos{}
	{};
	

	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();
	virtual ~Player() = default;
};
