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
	for (int source = 0; source < m_Colliders.size(); source++) //충돌레이어를 만들어서 계산량줄이고 //어떤 레이어끼리만 충돌할지는 미리 만들어놓기
	{
		for (int target = source; target < m_Colliders.size(); target++)
		{
			if (m_Colliders[source]->IsCollide(m_Colliders[target]) == false || source == target) //본인이랑 충돌처리한거같은데? 
				continue;
			if (m_Colliders[source]->GetCollisionType() == CollisionType::Block &&
				m_Colliders[target]->GetCollisionType() == CollisionType::Block)
			{
				m_Colliders[source]->ProcessBlock(m_Colliders[target]); 
				m_Colliders[target]->ProcessBlock(m_Colliders[source]); 
			}
			else
			{
				m_Colliders[source]->InsertCollideState(m_Colliders[target]); //충돌중인 콜라이더 목록에는
				m_Colliders[target]->InsertCollideState(m_Colliders[source]); //오버랩만 들어갈수있다.
			}
		}
	}
}

void CollisionManager::EraseCollider(Collider* remove)
{
	m_Colliders.erase(std::remove_if(m_Colliders.begin(), m_Colliders.end(),
		[remove](auto x) -> bool { return x == remove; }), m_Colliders.end());
}
