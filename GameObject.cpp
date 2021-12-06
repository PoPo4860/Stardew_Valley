#include "GameObject.h"

GameObject::GameObject() :
	pos{},
	rect{},
	bodySize{ NULL },
	img{ nullptr }
{}

bool GameObject::operator<(GameObject& b)
{
	return  pos.y < b.GetPosY();
}

