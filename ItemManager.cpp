#include "ToolItem.h"
#include "ItemManager.h"
void ItemManager::Init()
{
	ResourceItemInfo resource;
	ToolItemInfo tool;

	resource.gold = 1;
	resource.info = STONE_INFO;
	resourceItem.insert(make_pair(STONE, resource));

	resource.gold = 3;
	resource.info = COAL_INFO;
	resourceItem.insert(make_pair(COAL, resource));

	tool.attackSpeed = 5;
	tool.minDamage = 1;
	tool.maxDamage = 3;
	tool.gold = 10;
	tool.info = PICK_INFO;
	toolItme.insert(make_pair(PICK, tool));


}

void ItemManager::Update()
{
	for (int i = 0; i < resourceItemVector.size(); ++i)
		resourceItemVector[i].Update();
	for (int i = 0; i < toolItemVector.size(); ++i)
		toolItemVector[i].Update();
}

void ItemManager::Render(HDC hdc)
{

}

void ItemManager::Release()
{
	toolItme.clear();
	resourceItem.clear();
	ItemVectorClear();
	ReleaseSingleton();
}

void ItemManager::CreateResourceItem(int key, POINTFLOAT pos)
{
	ResourceItem obj(key, pos);
	resourceItemVector.push_back(obj);
}

void ItemManager::PushObjectQueue()
{
	for (int i = 0; i < resourceItemVector.size(); ++i)
		RENDER_MANAGER->PushObjectQueue(&resourceItemVector[i]);
	for (int i = 0; i < toolItemVector.size(); ++i)
		RENDER_MANAGER->PushObjectQueue(&toolItemVector[i]);
}

void ItemManager::ItemVectorClear()
{
	toolItemVector.clear();
	resourceItemVector.clear();
}
