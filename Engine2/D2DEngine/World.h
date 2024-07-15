#pragma once
#include "GameObject.h"
class AABB;
class GameObject;
class World
{
public:
	World();
	virtual ~World();	
	std::list<GameObject*> m_GameObjects;
	AABB* m_pCullingBound = nullptr; 
	AABB* m_CullingBoundDefault;	
public:	
	void Update(float deltaTime);
	void Render(ID2D1HwndRenderTarget* pRenderTarget);
	void Clear();
	void SetCullingBound(AABB* pBound) { m_pCullingBound = pBound; }
	// ���ø� �Լ��� GameObject�� �����Ѵ�.
	template<typename T>
	T* CreateGameObject()
	{
		bool bIsBase = std::is_base_of<GameObject, T>::value;
		assert(bIsBase == true);
		T* newObject = new T();
		newObject->SetOwner(this);
		for (auto it = m_GameObjects.begin(); it != m_GameObjects.end(); it++)
		{
			if ((*it)->renderOrder > newObject->renderOrder)
			{
				m_GameObjects.insert(it, newObject); 
				return newObject; //�־����� ����
			}			
		}

		m_GameObjects.push_back(newObject); //������ ��Ȳ�� ���ؼ��� �ڿ� �ֱ�
		
		return newObject;
	}

	void DeleteGAmeObject(GameObject* gameObject)
	{
		GameObject* del = gameObject; //�� ��������� ����ִٰ� �������ҵ�?
		m_GameObjects.erase(remove(m_GameObjects.begin(), m_GameObjects.end(), gameObject), m_GameObjects.end());
		delete del; //���� ������Ʈ ��Ͽ��� ����� ��¥ �����ϱ�.. 
	}
};

