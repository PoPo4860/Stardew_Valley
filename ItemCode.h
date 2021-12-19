#pragma once
#define STONE 1
#define STONE_NAME "��"
#define STONE_INFO "���۰� �Ǽ��� ����\n���Ǵ� ���� ���."
#define COAL 2
#define COAL_NAME "��ź"
#define COAL_INFO "���۰� ����Ȱ����\n���Ǵ� ���� ��\n�ٴ� ��"
#define COPPER 3
#define COPPER_NAME "����"
#define COPPER_INFO "�ֱ��� ������ ��\n�ִ� ���� ����"
#define STEEL 4
#define STEEL_NAME "ö����"
#define STEEL_INFO "�ֱ��� ������ ��\n�ִ� �׷����� ����\n����"
#define GOLD 5
#define GOLD_NAME "�ݱ���"
#define GOLD_INFO "�ֱ��� ������ ��\n�ִ� ���� ����"
#define IRIDIUM 6
#define IRIDIUM_NAME "�̸��� ����"
#define IRIDIUM_INFO "������ Ư���� ����\n�̱����� ����.\n �ֱ��� ������ ��\n�ֽ��ϴ�."

#define EMERALD 7
#define EMERALD_NAME "���޶���"
#define EMERALD_INFO "���� �ʷϺ��� ����."
#define TOPAZ 8
#define TOPAZ_NAME "������"
#define TOPAZ_INFO "���� ��������\n�Ƹ��ٿ���\n����ġ �ֽ��ϴ�."
#define AQUAMARINE 9
#define AQUAMARINE_NAME "����Ƹ���"
#define AQUAMARINE_INFO "�Ƹ��Ƹ� ������\nû�ϻ� ����."
#define RUBY 10
#define RUBY_NAME "���"
#define RUBY_INFO "���� ���� �Ƹ��ٿ�\n���� ���� ����\n�̵��� ���ϴ� ����."
#define AMETHYST 11
#define AMETHYST_NAME "�ڼ���"
#define AMETHYST_INFO "�������� ���� ����."
#define DIAMOND 12
#define DIAMOND_NAME "���̾Ƹ��"
#define DIAMOND_INFO "����ϰ� �����\n����."

#define STEEL_SHORT_SWORD 13
#define STEEL_SHORT_SWORD_NAME "��ö �Ұ�"
#define STEEL_SHORT_SWORD_INFO "�⺻���� �ݼ� ��"
#define PICK 14
#define PICK_NAME "���"
#define PICK_INFO "���� �μ� �� ����մϴ�."

#include <string>
#include"ItemCode.h"
using namespace std;

enum class ItemType { Empty, ToolItem, ResourceItem };

// ����������
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

// �ڿ�������
struct ResourceItemInfo
{
	ResourceItemInfo()
		:gold{ 0 }, info{ "" }, name{ "" }{}
	int gold;
	string name;
	string info;
};

