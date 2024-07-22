#include "pch.h"
#include "World.h"
#include "D2DRenderer.h"
#include "AABB.h"
#include "GameObject.h"
#include "Animation.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "CollisionManager.h"


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
	
	CollisionManager::GetInstance()->CollisionCheck(); //���� �����°� �����ʳ�?  �׷��� �Ǹ� �ݶ��̴��� ������Ʈ�� �ִ°� �ƴϰ�? 
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
