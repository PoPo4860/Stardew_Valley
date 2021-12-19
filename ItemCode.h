#pragma once
#define STONE 1
#define STONE_NAME "돌"
#define STONE_INFO "제작과 건설에 많이\n사용되는 흔한 재료."
#define COAL 2
#define COAL_NAME "석탄"
#define COAL_INFO "제작과 제련활동에\n사용되는 불이 잘\n붙는 돌"
#define COPPER 3
#define COPPER_NAME "구리"
#define COPPER_INFO "주괴로 제련할 수\n있는 흔한 광석"
#define STEEL 4
#define STEEL_NAME "철광석"
#define STEEL_INFO "주괴로 제련할 수\n있는 그럭저럭 흔한\n광석"
#define GOLD 5
#define GOLD_NAME "금광석"
#define GOLD_INFO "주괴로 제련할 수\n있는 귀한 광석"
#define IRIDIUM 6
#define IRIDIUM_NAME "이리듐 광석"
#define IRIDIUM_INFO "진기한 특성이 많은\n이국적인 광석.\n 주괴로 제련할 수\n있습니다."

#define EMERALD 7
#define EMERALD_NAME "에메랄드"
#define EMERALD_INFO "밝은 초록빛의 보석."
#define TOPAZ 8
#define TOPAZ_NAME "토파즈"
#define TOPAZ_INFO "흔한 편이지만\n아름다워서\n값어치 있습니다."
#define AQUAMARINE 9
#define AQUAMARINE_NAME "아쿠아마린"
#define AQUAMARINE_INFO "아른아른 빛나는\n청록색 보석."
#define RUBY 10
#define RUBY_NAME "루비"
#define RUBY_INFO "진한 색과 아름다운\n광택 덕에 많은\n이들이 원하는 보석."
#define AMETHYST 11
#define AMETHYST_NAME "자수정"
#define AMETHYST_INFO "보랏빛이 나는 석영."
#define DIAMOND 12
#define DIAMOND_NAME "다이아몬드"
#define DIAMOND_INFO "희귀하고 값비싼\n보석."

#define STEEL_SHORT_SWORD 13
#define STEEL_SHORT_SWORD_NAME "강철 소검"
#define STEEL_SHORT_SWORD_INFO "기본적인 금속 검"
#define PICK 14
#define PICK_NAME "곡괭이"
#define PICK_INFO "돌을 부술 때 사용합니다."

#include <string>
#include"ItemCode.h"
using namespace std;

enum class ItemType { Empty, ToolItem, ResourceItem };

// 도구아이템
struct ToolItemInfo
{
	ToolItemInfo()
		: maxDamage{ 0 }, minDamage{ 0 }, attackSpeed{ 0 }, gold{ 0 }, info{ "" }, name{""}{}
	int maxDamage;
	int minDamage;
	int attackSpeed;
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

