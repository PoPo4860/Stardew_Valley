#include "ItemManager.h"
#include <fstream>
#include <locale>
ItemManager::ItemManager() :toolItmeInfo{}, resourceItemInfo{}, itemVector{}
{}
void ItemManager::Init()
{
	ResourceItemInfo resource;
	ToolItemInfo tool;
	string str = "";

	// 자원 아이템 초기화
	fstream resourcefile("ItemInfo/ResourceItemInfo.txt");
	while (getline(resourcefile, str))
	{
		int itemCode = stoi(str);
		getline(resourcefile, str);
		resource.gold = stoi(str);
		getline(resourcefile, str);
		resource.name = str;
		getline(resourcefile, str);
		resource.info = str;
		resourceItemInfo.insert(make_pair(itemCode, resource));
	}

	// 도구아이템 초기화
	fstream toolfile("ItemInfo/ToolItemInfo.txt");
	while (getline(toolfile, str))
	{
		int itemCode = stoi(str);
		getline(toolfile, str);
		tool.gold = stoi(str);
		getline(toolfile, str);
		tool.minDamage = stoi(str);
		getline(toolfile, str);
		tool.maxDamage = stoi(str);
		getline(toolfile, str);
		tool.gold = stoi(str);
		getline(toolfile, str);
		tool.name = str;
		getline(toolfile, str);
		tool.info = str;
		toolItmeInfo.insert(make_pair(itemCode, tool));
	}
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
	ItemClear();
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
				SAFE_RELEASE((*iter));
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

void ItemManager::ItemClear()
{
	for (vector<Item*>::iterator iter = itemVector.begin();
		iter != itemVector.end(); ++iter)
	{	// 백터를 순회하며 삭제
		SAFE_RELEASE((*iter));
	}
	itemVector.clear();
	while (itemQueue.empty() == false)
	{
		itemQueue.pop();
	}
}
