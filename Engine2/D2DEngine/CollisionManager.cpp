#include "pch.h"
#include "CollisionManager.h"
#include "Collider.h"

CollisionManager* CollisionManager::inst = nullptr;

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}

CollisionManager* CollisionManager::GetInstance()
{
	if (inst == nullptr) {
		inst = new CollisionManager();
	}
	return inst;
}

void CollisionManager::CollisionCheck()
{
	for (int source = 0; source < m_Colliders.size(); source++)
	{
		for (int target = source; target < m_Colliders.size(); target++)
		{
			if (m_Colliders[source]->IsCollide(m_Colliders[target]) == false || source == target) //본인이랑 충돌처리한거같은데? 
				continue;
			if (m_Colliders[source]->GetCollisionType() == CollisionType::Block &&
				m_Colliders[target]->GetCollisionType() == CollisionType::Block)
			{
				m_Colliders[source]->ProcessBlock(m_Colliders[target]); //움직이지 않는 콜라이더는 또 어떻게 구분하지? 
				m_Colliders[target]->ProcessBlock(m_Colliders[source]); //남들이 유니티랑 비슷한 구조로 짠다는거는 구조를 보고 예측해봤다는건가? 
			}
			else
			{
				m_Colliders[source]->InsertCollideState(m_Colliders[target]); //충돌중인 콜라이더 목록에는
				m_Colliders[target]->InsertCollideState(m_Colliders[source]); //오버랩만 들어갈수있다.
			}
		}
	}
}