#include "pch.h"
#include "World.h"
#include "D2DRenderer.h"
#include "AABB.h"
#include "GameObject.h"
#include "Animation.h"
#include "Collider.h"
#include "BoxCollider.h"


World::World()
{
	float width = 640;
	float height = 480;
	m_CullingBoundDefault = new AABB;
	m_CullingBoundDefault->SetExtent(width/2, height/2);//���뼺�� �����Ѱ�? ����۰� ������ ������ ���� ��ȣ ������..
	m_CullingBoundDefault->SetCenter(0,0);
	SetCullingBound(m_CullingBoundDefault);	
}

World::~World()
{

}


void World::Update(float deltaTime)
{
	for (auto& obj : m_GameObjects)
	{
		obj->Update(deltaTime);
	}
	
	CollisionCheck(); //���� �����°� �����ʳ�?  �׷��� �Ǹ� �ݶ��̴��� ������Ʈ�� �ִ°� �ƴϰ�? 
	//���� �̻��ѵ� �ݶ��̴��� ������Ʈ�� �ְ������.. ��.. 
}

void World::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	for (auto& obj : m_GameObjects) 
	{		
		if (this->m_pCullingBound->CheckIntersect(obj->GetBoundBox())) 
		{
			obj->Render(pRenderTarget);
		}		
	}
}

void World::Clear()
{
	m_GameObjects.clear();
}

void World::CollisionCheck()
{
	//m_Colliders.clear();
	//for (auto& obj : m_GameObjects)
	//{
	//	BoxCollider* col = obj->GetComponent<BoxCollider>();
	//	if (col)
	//	{
	//		m_Colliders.push_back(col);
	//	}
	//}

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

void World::InsertColliders(GameObject* newObject)
{
	for (int i = 0; i < newObject->m_OwnedComponents.size(); i++)
	{
		Collider* col = dynamic_cast<BoxCollider*>(newObject->m_OwnedComponents[i]);
		if (col != nullptr)
		{
			m_Colliders.push_back(col); //������Ʈ���� �����ɶ��� ������ ������ �����ֵ�������. �̷��͵��� ����Ʈ �����͸� ���� �ǳ�? 
			return;
		}
	}
}
