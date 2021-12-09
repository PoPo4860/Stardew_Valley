#pragma once
#include "GameEntity.h"
class Image;
class GameObject : public GameEntity
{
protected:	// 상속된 클래스에 노출시킨다.
	POINTFLOAT pos;
	RECT rect;
	Image* img;
	int bodySize;
public:
	GameObject();
	virtual ~GameObject() = default;

	inline void SetPos(POINTFLOAT pos) { this->pos = pos; }
	inline POINTFLOAT GetPos() { return this->pos; }
	inline float GetPosY() const { return  this->pos.y; }
	inline int GetBodySize() { return this->bodySize; }
	inline RECT GetRect() { return this->rect; }
};

class Interaction : public GameObject
{

public:
	virtual bool InteractionPick(int damage) { return false; }
	virtual bool InteractionSword(int damage) { return false; };
	virtual void InteractionRightClick() {};
	virtual ~Interaction() = default;
};

class Character
{
protected:
	float moveSpeed;
	int hp;
public:
	virtual ~Character() = default;
};


