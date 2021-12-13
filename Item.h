#pragma once
#include "GameObject.h"
enum class ItemInfo { ToolItem, ResourceItem };
class Item : public GameObject
{
private:
protected:
	ItemInfo itemInfo;
	POINTFLOAT landPos;
	POINTFLOAT moveSpeed;
	float gravity;
public:
	ItemInfo GetItemInfo() { return itemInfo; }
	void PlayerFollow();
	void GravityAction();
	void ItemInit();
	Item();
	virtual ~Item() = default;
};

