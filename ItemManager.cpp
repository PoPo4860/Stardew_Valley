#include "ItemManager.h"
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
		itemVector[i].Update();
}

void ItemManager::Render(HDC hdc)
{

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
	Item obj(key, pos);
	itemVector.push_back(obj);
}

void ItemManager::PushObjectQueue()
{
	for (int i = 0; i < itemVector.size(); ++i)
		RENDER_MANAGER->PushObjectQueue(&itemVector[i]);

}

void ItemManager::ItemVectorClear()
{
	itemVector.clear();
}
