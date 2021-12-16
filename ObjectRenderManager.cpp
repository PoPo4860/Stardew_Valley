#include "ObjectRenderManager.h"

void ObjectRenderManager::PushObjectVector(GameObject* obj)
{
	for (vector<GameObject*>::iterator iter = objectVector.begin();
		iter != objectVector.end(); ++iter)
	{	// �迭�� �ֱ� ���� ���͸� ��ȸ�ϸ� ��
		if ((*iter) == obj)
		{
			cout << "ObjectRenderManager::PushObjectQueue : �̹� ���Ϳ� ���� ������Ʈ�� ����" << "\n";
			return;
		}	// �̹� �ڱ� �ڽ��� �� �ִٸ� �Լ� ����
	}

	objectVector.push_back(obj);
	// ���Ϳ� �������� ������Ʈ�� �߰�
	VectorSort();
}

void ObjectRenderManager::DeleteObjectVector(GameObject* obj)
{
	for (vector<GameObject*>::iterator iter = objectVector.begin();
		iter != objectVector.end(); ++iter)
	{	// ���͸� ��ȸ�ϸ� ����
		if ((*iter) == obj)
		{
			objectVector.erase(iter);
			return;
		}
	}
	cout << "ObjectRenderManager::DeleteObjectVectr : ������ ������Ʈ�� ã�� ����" << "\n";
}	// ������ ���� ����

void ObjectRenderManager::ObjectRender(HDC hdc)
{
	VectorSort();
	// ���͸� ����
	int num = 0;
	for (vector<GameObject*>::iterator iter = objectVector.begin();
		iter != objectVector.end(); 
		++iter)
	{	// ���͸� ��ȸ�ϸ� ����
		(*iter)->Render(hdc);
		++num;
	}
}

void ObjectRenderManager::VectorClear()
{
	for (vector<GameObject*>::iterator iter = objectVector.begin();
		iter != objectVector.end();)
	{	// ���͸� ��ȸ�ϸ� ����
		iter= objectVector.erase(iter);
	}
	objectVector.clear();
}	// ���� Ŭ����

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
	// ���͸� ����
}
