#pragma once
#include "Config.h"
#include "GameObject.h"
#include <queue>
struct compare
{
	bool operator()(GameObject* a, GameObject* b)
	{
		return a->GetPosY() > b->GetPosY();
	}
};
class ObjectRenderManager : public Singleton<ObjectRenderManager>
{
private:
	priority_queue<GameObject*, vector<GameObject*>, compare> objectQueue;
public:
	void Init() {}
	void PushObjectQueue(GameObject* obj);
	void ObjectRender(HDC hdc);
	void QueueClear();
	void Release();

};

