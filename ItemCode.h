#pragma once
#define STONE 1
#define STONE_INFO "제작과 건설에 많이 사용되는 흔한 재료."
#define COAL 2
#define COAL_INFO "제작과 제련활동에 사용되는 불이 잘 붙는 돌"
#define PICK 10
#define PICK_INFO "돌을 부술 때 사용합니다."
#include <string>

using namespace std;
struct ToolItemInfo
{
	int maxDamage;
	int minDamage;
	int attackSpeed;
	int gold;
	string info;
};

// 자원아이템
struct ResourceItemInfo
{
	int gold;
	string info;
};
