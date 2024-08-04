#include "pch.h"
#include "CollisionManager.h"
#include "Collider.h"

CollisionManager* CollisionManager::inst = nullptr;

CollisionManager::CollisionManager()
{
	collisonLayer.insert(std::make_pair(CollisionLayer::Tower,CollisionLayer::Enemy));
	collisonLayer.insert(std::make_pair(CollisionLayer::Tower,CollisionLayer::Bullet));
	collisonLayer.insert(std::make_pair(CollisionLayer::Enemy,CollisionLayer::Bullet));
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

void CollisionManager::CollisionCheck() //��ϵ� �浹���̾���� �˻��ϵ��� �ؾ��ϴϱ� ���̾�� �ݶ��̴��� ����־����.. 
{
	for (auto val : collisonLayer)
	{
		for (int source = 0; source < colliders[val.first].size(); source++)  
		{
			for (int target = source; target < colliders[val.second].size(); target++)
			{
				
				if (colliders[val.first][source]->GetCollisionType() == CollisionType::Block &&
					colliders[val.second][target]->GetCollisionType() == CollisionType::Block)
				{
					colliders[val.first][source]->ProcessBlock(colliders[val.first][source],colliders[val.second][target]); //���� ai�� ���� .. Ʈ���ŵ�鵵.. ���������ϱ�.. ���⼭ �ʹ� ���� �˰����� ����ϸ�ȵǴµ�.. 
					colliders[val.second][target]->ProcessBlock(colliders[val.second][target],colliders[val.first][source]);//������ Ž���˰����� �׳� �ݶ��̴����״ϱ�.. �������� �ݶ��̴��� �����Ҽ��־����. 
				}
				else
				{
					colliders[val.first][source]->InsertCollideState(colliders[val.second][target]); //�浹���� �ݶ��̴� ��Ͽ���
					colliders[val.second][target]->InsertCollideState(colliders[val.first][source]); //�������� �����ִ�.
				}
			}
		}
	}

	for (auto cols : colliders)
	{
		for (int i = 0; i < cols.second.size(); i++)
		{
			cols.second[i]->ProcessOverlap(); //��� ��ó���� ��ø���¿� ���� ó���� �����ֱ�...
		}
	}
}

void CollisionManager::EraseCollider(Collider* remove)
{
	CollisionLayer layer = remove->GetCollisionLayer();
	colliders[layer].erase(std::remove_if(colliders[layer].begin(), colliders[layer].end(),
		[remove](auto x) -> bool { return x == remove; }), colliders[layer].end());
}

void CollisionManager::pushCollider(Collider* col)
{
	colliders[col->GetCollisionLayer()].push_back(col); 
}
