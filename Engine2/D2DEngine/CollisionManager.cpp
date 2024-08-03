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
	for (int source = 0; source < colliders.size(); source++) //충돌레이어를 만들어서 계산량줄이고 //어떤 레이어끼리만 충돌할지는 미리 만들어놓기
	{
		for (int target = source; target < colliders.size(); target++)
		{
			if (colliders[source]->IsCollide(colliders[target]) == false || source == target) //본인이랑 충돌처리한거같은데? 
				continue;
			if (colliders[source]->GetCollisionType() == CollisionType::Block &&
				colliders[target]->GetCollisionType() == CollisionType::Block)
			{
				colliders[source]->ProcessBlock(colliders[target]); 
				colliders[target]->ProcessBlock(colliders[source]); 
			}
			else
			{
				colliders[source]->InsertCollideState(colliders[target]); //충돌중인 콜라이더 목록에는
				colliders[target]->InsertCollideState(colliders[source]); //오버랩만 들어갈수있다.
			}
		}
	}
}

void CollisionManager::EraseCollider(Collider* remove)
{
	colliders.erase(std::remove_if(colliders.begin(), colliders.end(),
		[remove](auto x) -> bool { return x == remove; }), colliders.end());
}
