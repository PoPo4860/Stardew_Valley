#pragma once
#include "ItemCode.h"
#include "Image.h"
class InventoryItem
{
public:
	InventoryItem() :itemType{ ItemType::Empty }, toolItemInfo{}, resourceItemInfo{}{}
	ItemType itemType;
	ToolItemInfo* toolItemInfo;
	ResourceItemInfo* resourceItemInfo;
	Image* img;
	void Release()
	{
		itemType = ItemType::Empty;
		delete toolItemInfo;
		delete resourceItemInfo;
		delete img;
		toolItemInfo = nullptr;
		resourceItemInfo = nullptr;
		img = nullptr;
	};

	const ToolItemInfo GetToolItemInfo() { return *toolItemInfo; }
	const ResourceItemInfo GetResourceItemInfo() { return *resourceItemInfo; }

	void SetToolItemInfo(ToolItemInfo item) { toolItemInfo = &item; }
	void SetResourceItemInfo(ResourceItemInfo item) { resourceItemInfo = &item; }
};

