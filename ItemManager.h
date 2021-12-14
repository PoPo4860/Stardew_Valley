#pragma once
#include "Config.h"
#include "GameObject.h"
#include "Item.h"
#include "ItemCode.h"
#include <unordered_map>
class ItemManager : public Singleton<ItemManager>
{
private:
	unordered_map<int, ToolItemInfo> toolItmeInfo;
	unordered_map<int, ResourceItemInfo> resourceItemInfo;
	vector<Item> itemVector;

public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();
public:
	ToolItemInfo GetToolItem(int key) { return toolItmeInfo.at(key);}
	ResourceItemInfo GetResourceItem(int key) { return resourceItemInfo.at(key);}
	void CreateResourceItem(int key, POINTFLOAT pos);
	void PushObjectQueue();
	void ItemVectorClear();
};

