#pragma once
#include "Config.h"
#include "GameObject.h"
#include "Item.h"
#include "ItemCode.h"
#include "ToolItem.h"
#include "ResourceItem.h"
#include <unordered_map>
class ItemManager : public Singleton<ItemManager>
{
private:
	unordered_map<int, ToolItemInfo> toolItme;
	unordered_map<int, ResourceItemInfo> resourceItem;
	vector<ResourceItem> resourceItemVector;
	vector<ToolItem> toolItemVector;

public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();
public:
	ToolItemInfo GetToolItem(int key) { return toolItme.at(key);}
	ResourceItemInfo GetResourceItem(int key) { return resourceItem.at(key);}
	void CreateResourceItem(int key, POINTFLOAT pos);
	void PushObjectQueue();
	void ItemVectorPush(ResourceItem obj) { resourceItemVector.push_back(obj); }
	void ItemVectorPush(ToolItem obj) { toolItemVector.push_back(obj); }
	void ItemVectorClear();
};

