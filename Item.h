#pragma once
#include "GameObject.h"
#include "ItemCode.h"

struct Move 
{
	Move()
		:landPos{}, gravity{}, gravityCheck{ true }, time{}, speed{}
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

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	Item(int key, POINTFLOAT pos);
	virtual ~Item() = default;
public:
	ItemType GetItemInfo() { return itemType; }
	bool PlayerFollow();
	void GravityAction();
};

