#include "ItemManager.h"
ItemManager::ItemManager() :toolItmeInfo{}, resourceItemInfo{}, itemVector{}
{}
void ItemManager::Init()
{
	ResourceItemInfo resource;
	ToolItemInfo tool;

	resource.gold = 1;
	resource.info = STONE_INFO;
	resourceItemInfo.insert(make_pair(STONE, resource));

	resource.gold = 3;
	resource.info = COAL_INFO;
	resourceItemInfo.insert(make_pair(COAL, resource));

	tool.attackSpeed = 5;
	tool.minDamage = 1;
	tool.maxDamage = 3;
	tool.gold = 10;
	tool.info = PICK_INFO;
	toolItmeInfo.insert(make_pair(PICK, tool));
}

void ItemManager::Update()
{
	for (int i = 0; i < itemVector.size(); ++i)
		itemVector[i]->Update();
}

void ItemManager::Release()
{
	toolItmeInfo.clear();
	resourceItemInfo.clear();
	ItemVectorClear();
	ReleaseSingleton();
}

void ItemManager::CreateResourceItem(int key, POINTFLOAT pos)
{
	itemVector.push_back(new Item (key, pos));
}

void ItemManager::DeleteObjectVector(Item* obj)
{
	for (vector<Item*>::iterator iter = itemVector.begin();
		iter != itemVector.end();++iter)
	{	// 백터를 순회하며 삭제
		if ((*iter) == obj)
		{
			itemVector.erase(iter);
			return;
		}
	}
}

void ItemManager::ItemVectorClear()
{
	for (vector<Item*>::iterator iter = itemVector.begin();
		iter != itemVector.end();)
	{	// 백터를 순회하며 삭제
		(*iter)->Release();
		iter = itemVector.erase(iter);
	}
	itemVector.clear();
}
