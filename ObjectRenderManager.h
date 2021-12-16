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
	//priority_queue<GameObject*, vector<GameObject*>, compare> objectQueue;
	vector<GameObject*> objectVector;


public:
	void Init() {}
	void PushObjectVector(GameObject* obj);
	void DeleteObjectVector(GameObject* obj);
	void ObjectRender(HDC hdc);
	void VectorClear();
	void Release();
	void VectorSort();
};

