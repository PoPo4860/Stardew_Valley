#pragma once
#include "GameObject.h"
#include "ItemCode.h"

struct Move 
{
	Move()
		:landPos{ 0 }, gravity{ 0 }, gravityCheck{ true }, time{ 0 }, speed{ 0 }
	{}
	POINTFLOAT speed;
	float landPos;
	float gravity;
	bool gravityCheck;
	float time;
};
class Item : public GameObject
{
private:
	ItemType itemType;
	ResourceItemInfo info;
	Move move;
	int itemNum;
public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	Item(int key, POINTFLOAT pos, int itemNum = 1);
	virtual ~Item() = default;
public:
	ItemType GetItemInfo() { return itemType; }
	bool PlayerFollow();
	void GravityAction();
};

