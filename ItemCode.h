#pragma once
#define STONE 1
#define COAL 2
#define COPPER 3
#define STEEL 4
#define GOLD 5
#define IRIDIUM 6

#define EMERALD 7
#define TOPAZ 8
#define AQUAMARINE 9
#define RUBY 10
#define AMETHYST 11
#define DIAMOND 12

#define STEEL_SHORT_SWORD 13
#define PICK 14

#include <string>
#include"ItemCode.h"
using namespace std;

enum class ItemType { Empty, ToolItem, ResourceItem };

// 도구아이템
struct ToolItemInfo
{
	ToolItemInfo()
		: maxDamage{ 0 }, minDamage{ 0 }, gold{ 0 }, info{ "" }, name{""}{}
	int maxDamage;
	int minDamage;
	int gold;
	string name;
	string info;
};

// 자원아이템
struct ResourceItemInfo
{
	ResourceItemInfo()
		:gold{ 0 }, info{ "" }, name{ "" }{}
	int gold;
	string name;
	string info;
};

