#include "ObjectRenderManager.h"

void ObjectRenderManager::PushObjectVector(GameObject* obj)
{
	for (vector<GameObject*>::iterator iter = objectVector.begin();
		iter != objectVector.end(); ++iter)
	{	// 배열에 넣기 전에 백터를 순회하며 비교
		if ((*iter) == obj)
		{
			cout << "ObjectRenderManager::PushObjectQueue : 이미 벡터에 같은 오브젝트가 있음" << "\n";
			return;
		}	// 이미 자기 자신이 들어가 있다면 함수 종료
	}

	objectVector.push_back(obj);
	// 백터에 렌더해줄 오브젝트를 추가
	VectorSort();
}

void ObjectRenderManager::DeleteObjectVector(GameObject* obj)
{
	for (vector<GameObject*>::iterator iter = objectVector.begin();
		iter != objectVector.end(); ++iter)
	{	// 백터를 순회하며 삭제
		if ((*iter) == obj)
		{
			objectVector.erase(iter);
			return;
		}
	}
	cout << "ObjectRenderManager::DeleteObjectVectr : 삭제할 오브젝트를 찾지 못함" << "\n";
}	// 벡터의 원소 삭제

void ObjectRenderManager::ObjectRender(HDC hdc)
{
	VectorSort();
	// 백터를 정렬
	int num = 0;
	for (vector<GameObject*>::iterator iter = objectVector.begin();
		iter != objectVector.end(); 
		++iter)
	{	// 백터를 순회하며 렌더
		(*iter)->Render(hdc);
		++num;
	}
}

void ObjectRenderManager::VectorClear()
{
	for (vector<GameObject*>::iterator iter = objectVector.begin();
		iter != objectVector.end();)
	{	// 백터를 순회하며 삭제
		iter= objectVector.erase(iter);
	}
	objectVector.clear();
}	// 백터 클리어

void ObjectRenderManager::Release()
{
	VectorClear();
	ReleaseSingleton();
}

void ObjectRenderManager::VectorSort()
{
	sort(objectVector.begin(), objectVector.end(),
		[](const GameObject* a, const GameObject* b)
		{
			return a->GetPosY() < b->GetPosY();
		});
	// 백터를 정렬
}
