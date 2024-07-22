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
			if (m_Colliders[source]->IsCollide(m_Colliders[target]) == false || source == target) //�����̶� �浹ó���ѰŰ�����? 
				continue;
			if (m_Colliders[source]->GetCollisionType() == CollisionType::Block &&
				m_Colliders[target]->GetCollisionType() == CollisionType::Block)
			{
				m_Colliders[source]->ProcessBlock(m_Colliders[target]); //�������� �ʴ� �ݶ��̴��� �� ��� ��������? 
				m_Colliders[target]->ProcessBlock(m_Colliders[source]); //������ ����Ƽ�� ����� ������ §�ٴ°Ŵ� ������ ���� �����غôٴ°ǰ�? 
			}
			else
			{
				m_Colliders[source]->InsertCollideState(m_Colliders[target]); //�浹���� �ݶ��̴� ��Ͽ���
				m_Colliders[target]->InsertCollideState(m_Colliders[source]); //�������� �����ִ�.
			}
		}
	}
}