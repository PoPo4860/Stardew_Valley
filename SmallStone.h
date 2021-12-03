#pragma once
#include "GameObject.h"
class SmallStone : GameObject
{
private:
	int frame;
public:
	SmallStone(int num = 0)
		:frame{ num }
	{}
	virtual void InteractionPick() override;
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();
};

