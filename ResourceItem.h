#pragma once
#include "Item.h"
#include "ItemCode.h"
class ResourceItem : public Item
{
private:
	ResourceItemInfo info;
protected:
public:
	ResourceItem(int key, POINTFLOAT pos);
	virtual ~ResourceItem() = default;
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
};

