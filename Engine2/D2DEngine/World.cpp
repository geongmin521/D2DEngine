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
	m_CullingBoundDefault->SetExtent(width/2, height/2);//재사용성이 가능한거? 데모앱과 엔진의 기준이 좀더 모호 해지네..
	m_CullingBoundDefault->SetCenter(0,0);
	SetCullingBound(m_CullingBoundDefault);	
}

World::~World()
{

}


void World::Update(float deltaTime)
{
	for (auto& obj : m_GameObjects) //필요한 오브젝트는 처음 월드에서 생성해줘야지.. 
	{
		obj->Update(deltaTime);
	}
	
	CollisionCheck();
	
}

void World::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	for (auto& obj : m_GameObjects) //카메라는 월드의 바운드 박스를 들고있어야하고...
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
				//충돌처리
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



//set은 내부적으로 어떻게구현되어있을려나..
