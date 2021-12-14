#pragma once
#define STONE 1
#define STONE_INFO "���۰� �Ǽ��� ���� ���Ǵ� ���� ���."
#define COAL 2
#define COAL_INFO "���۰� ����Ȱ���� ���Ǵ� ���� �� �ٴ� ��"
#define PICK 10
#define PICK_INFO "���� �μ� �� ����մϴ�."
#include <string>

using namespace std;

enum class ItemType { ToolItem, ResourceItem };

struct ToolItemInfo
{
	ToolItemInfo()
		: maxDamage{ 0 }, minDamage{ 0 }, attackSpeed{ 0 }, gold{ 0 }, info{""}{}
	int maxDamage;
	int minDamage;
	int attackSpeed;
	int gold;
	string info;
};

// �ڿ�������
struct ResourceItemInfo
{
	ResourceItemInfo()
		:gold{ 0 }, info{ "" }{}
	int gold;
	string info;
};
