#pragma once
#include "GameObject.h"
#include "MapInfo.h"
class SmallStone : public GameObject
{
private:
	Stone_Object_Info objectInfo;
	int frame;
public:
	SmallStone(Stone_Object_Info obj, int x, int y)
		:frame{NULL}, objectInfo{obj}
	{pos.x = (float)x, pos.y = (float)y; }
	virtual bool InteractionPick(int damage) override;
	virtual HRESULT Init() override;
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();
};

