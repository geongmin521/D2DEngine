#pragma once
#include "GameObject.h"

class AABB;
//class GameObject;
class Collider;
class BoxCollider;
class World
{
public:
	World();
	virtual ~World();	
	std::list<GameObject*> m_GameObjects;
	std::vector<Collider*> m_Colliders; //이것도 겹칠필요없으니까 set으로 이것도좀더 공부해야하긴해야하는데.. 
	AABB* m_pCullingBound = nullptr; 
	AABB* m_CullingBoundDefault;	
public:	
	void Update(float deltaTime);
	void Render(ID2D1HwndRenderTarget* pRenderTarget);
	void Clear();
	void SetCullingBound(AABB* pBound) { m_pCullingBound = pBound; }
	void CollisionCheck();

	// 템플릿 함수로 GameObject를 생성한다. 템플릿때문이였나? 
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
				return newObject; //넣었으면 종료
			}			
		}

		m_GameObjects.push_back(newObject); //나머지 상황에 대해서는 뒤에 넣기

		return newObject;
	}

	void DeleteGameObject(GameObject* gameObject)
	{
		GameObject* del = gameObject; //음 지우기전에 담고있다가 지워야할듯?
		m_GameObjects.erase(remove(m_GameObjects.begin(), m_GameObjects.end(), gameObject), m_GameObjects.end());
		delete del; //먼저 오브젝트 목록에서 지우고 진짜 삭제하기.. 
	}
};

