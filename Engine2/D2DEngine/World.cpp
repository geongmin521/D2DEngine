#include "pch.h"
#include "World.h"
#include "D2DRenderer.h"
#include "AABB.h"
#include "GameObject.h"
#include "Animation.h"
#include "Collider.h"


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
	for (auto& obj : m_GameObjects) //�ʿ��� ������Ʈ�� ó�� ���忡�� �����������.. 
	{
		obj->Update(deltaTime);
	}
	
	CollisionCheck();
	
}

void World::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	for (auto& obj : m_GameObjects) //ī�޶�� ������ �ٿ�� �ڽ��� ����־���ϰ�...
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
	
	for (int source = 0; source < m_Colliders.size(); source++)
	{
		for (int target = source; target < m_Colliders.size(); target++)
		{
			if (m_Colliders[source]->IsCollide(m_Colliders[target]) == false)
				continue;
			if (m_Colliders[source]->GetCollisionType() == CollisionType::Block &&
				m_Colliders[target]->GetCollisionType() == CollisionType::Block)
			{
				//�浹ó��
				m_Colliders[source]->ProcessBlock(m_Colliders[target]);
				m_Colliders[target]->ProcessBlock(m_Colliders[source]);
			}
			else
			{
				m_Colliders[source]->InsertCollideState(m_Colliders[target]); //�浹���� �ݶ��̴� ��Ͽ���
				m_Colliders[target]->InsertCollideState(m_Colliders[source]); //�������� �����ִ�.
			}
		}
	}
}



//set�� ���������� ��Ա����Ǿ���������..
