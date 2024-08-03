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
	for (int source = 0; source < colliders.size(); source++) //�浹���̾ ���� ��귮���̰� //� ���̾���� �浹������ �̸� ��������
	{
		for (int target = source; target < colliders.size(); target++)
		{
			if (colliders[source]->IsCollide(colliders[target]) == false || source == target) //�����̶� �浹ó���ѰŰ�����? 
				continue;
			if (colliders[source]->GetCollisionType() == CollisionType::Block &&
				colliders[target]->GetCollisionType() == CollisionType::Block)
			{
				colliders[source]->ProcessBlock(colliders[target]); 
				colliders[target]->ProcessBlock(colliders[source]); 
			}
			else
			{
				colliders[source]->InsertCollideState(colliders[target]); //�浹���� �ݶ��̴� ��Ͽ���
				colliders[target]->InsertCollideState(colliders[source]); //�������� �����ִ�.
			}
		}
	}
}

void CollisionManager::EraseCollider(Collider* remove)
{
	colliders.erase(std::remove_if(colliders.begin(), colliders.end(),
		[remove](auto x) -> bool { return x == remove; }), colliders.end());
}
