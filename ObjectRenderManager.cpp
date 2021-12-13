#include "ObjectRenderManager.h"

void ObjectRenderManager::PushObjectQueue(GameObject* obj)
{
	objectQueue.push(obj);
}

void ObjectRenderManager::ObjectRender(HDC hdc)
{
	while (objectQueue.empty() == false)
	{
		objectQueue.top()->Render(hdc);
		objectQueue.pop();
	}
}

void ObjectRenderManager::QueueClear()
{
	while (objectQueue.empty() == false)
	{
		objectQueue.pop();
	}
}

void ObjectRenderManager::Release()
{
	while (objectQueue.empty() == false)
	{
		objectQueue.pop();
	}
	ReleaseSingleton();
}
