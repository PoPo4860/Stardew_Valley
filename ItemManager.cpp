#include "ItemManager.h"
ItemManager::ItemManager() :toolItmeInfo{}, resourceItemInfo{}, itemVector{}
{}
void ItemManager::Init()
{
	ResourceItemInfo resource;
	ToolItemInfo tool;

	resource.gold = 1;
	resource.info = STONE_INFO;
	resource.name = STONE_NAME;
	resourceItemInfo.insert(make_pair(STONE, resource));

	resource.gold = 2;
	resource.info = COAL_INFO;
	resource.name = COAL_NAME;
	resourceItemInfo.insert(make_pair(COAL, resource));

	resource.gold = 5;
	resource.info = COPPER_INFO;
	resource.name = COPPER_NAME;
	resourceItemInfo.insert(make_pair(COPPER, resource));

	resource.gold = 7;
	resource.info = STEEL_INFO;
	resource.name = STEEL_NAME;
	resourceItemInfo.insert(make_pair(STEEL, resource));

	resource.gold = 10;
	resource.info = GOLD_INFO;
	resource.name = GOLD_NAME;
	resourceItemInfo.insert(make_pair(GOLD, resource));

	resource.gold = 10;
	resource.info = IRIDIUM_INFO;
	resource.name = IRIDIUM_NAME;
	resourceItemInfo.insert(make_pair(IRIDIUM, resource));

	resource.gold = 30;
	resource.info = EMERALD_INFO;
	resource.name = EMERALD_NAME;
	resourceItemInfo.insert(make_pair(EMERALD, resource));

	resource.gold = 50;
	resource.info = TOPAZ_INFO;
	resource.name = TOPAZ_NAME;
	resourceItemInfo.insert(make_pair(TOPAZ, resource));

	resource.gold = 70;
	resource.info = AQUAMARINE_INFO;
	resource.name = AQUAMARINE_NAME;
	resourceItemInfo.insert(make_pair(AQUAMARINE, resource));

	resource.gold = 100;
	resource.info = RUBY_INFO;
	resource.name = RUBY_NAME;
	resourceItemInfo.insert(make_pair(RUBY, resource));

	resource.gold = 150;
	resource.info = AMETHYST_INFO;
	resource.name = AMETHYST_NAME;
	resourceItemInfo.insert(make_pair(AMETHYST, resource));

	resource.gold = 500;
	resource.info = DIAMOND_INFO;
	resource.name = DIAMOND_NAME;
	resourceItemInfo.insert(make_pair(DIAMOND, resource));

	tool.attackSpeed = 7;
	tool.minDamage = 3;
	tool.maxDamage = 5;
	tool.gold = 10;
	tool.info = STEEL_SHORT_SWORD_INFO;
	tool.name = STEEL_SHORT_SWORD_NAME;
	toolItmeInfo.insert(make_pair(STEEL_SHORT_SWORD, tool));

	tool.attackSpeed = 5;
	tool.minDamage = 1;
	tool.maxDamage = 2;
	tool.gold = 10;
	tool.info = PICK_INFO;
	tool.name = PICK_NAME;
	toolItmeInfo.insert(make_pair(PICK, tool));

}

void ItemManager::Update()
{
	DeleteObjectVector();
	for (vector<Item*>::iterator iter = itemVector.begin();
		iter != itemVector.end();
		++iter)
	{
		(*iter)->Update();
	}
}

void ItemManager::Release()
{
	toolItmeInfo.clear();
	resourceItemInfo.clear();
	ItemVectorClear();
	ReleaseSingleton();
}

void ItemManager::CreateResourceItem(int key, POINTFLOAT pos, int num)
{
	itemVector.push_back(new Item (key, pos , num));
}

void ItemManager::DeleteObjectVector()
{
	while (itemQueue.empty() == false)
	{
		for (vector<Item*>::iterator iter = itemVector.begin();
			iter != itemVector.end(); ++iter)
		{	// 백터를 순회하며 삭제
			if ((*iter) == itemQueue.front())
			{
				itemVector.erase(iter);
				itemQueue.pop();
				break;
			}
		}
	}
}

void ItemManager::DeleteObject(Item* obj)
{
	itemQueue.push(obj);
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
	while (itemQueue.empty() == false)
	{
		itemQueue.pop();
	}
}
