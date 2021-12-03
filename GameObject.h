#pragma once

// ������ ������� ������ ���� �⺻���� ������ �Ǵ� Ŭ����
// �ʱ�ȭ (�޸� �Ҵ�), 1ȸ�� ����
// ������Ʈ, ���������� �����Ӹ��� ����
// ���, ���������� �����Ӹ��� ����
// �޸� ����, 1ȸ�� ����

/*
	��� : �ߺ��Ǵ� �ڵ带 ���� �� �ִ�.
	�߻�ȭ : ���Ǽ��迡 �ִ� ��ü�� ���Ӱ�ü�� �ʿ��� �����͸� �߷��� ��.

	Ŭ���� �߻�ȭ : Ŭ���� �� ����Ǵ� ������� �߷��� ��.
*/

#include "GameEntity.h"

class Image;
class GameObject : public GameEntity
{
//private:	// �ܺ� Ŭ������ �����Ű�� �ʴ´�.
protected:	// ��ӵ� Ŭ������ �����Ų��.
//public:		// ��� �ܺ� Ŭ������ �����Ų��.
	POINTFLOAT pos;
	RECT rect;
	float moveSpeed;
	int bodySize;
	int hp;
	Image* img;

public:
	GameObject() :
		pos{},
		rect{},
		moveSpeed{ NULL },
		bodySize{ NULL },
		hp{ NULL }, 
		img{ nullptr }
	{}
	virtual ~GameObject() = default;
	virtual void InteractionPick() {};
	virtual void InteractionSword(int damage) {};
	virtual void InteractionRightClick() {};

	
	inline void SetPos(POINTFLOAT pos) { this->pos = pos; }
	inline POINTFLOAT GetPos() { return this->pos; }
	inline void SetMoveSpeed(float speed) { this->moveSpeed = speed; }
	inline int GetBodySize() { return this->bodySize; }

};

