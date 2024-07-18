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
	m_CullingBoundDefault->SetExtent(width/2, height/2);//재사용성이 가능한거? 데모앱과 엔진의 기준이 좀더 모호 해지네..
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
	
	CollisionCheck(); //따로 돌리는게 맞지않나?  그렇게 되면 콜라이더는 컴포넌트에 넣는게 아니고? 
	//뭔가 이상한데 콜라이더는 컴포넌트로 넣고싶은데.. 흠.. 
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

void World::InsertColliders(GameObject* newObject)
{
	for (int i = 0; i < newObject->m_OwnedComponents.size(); i++)
	{
		Collider* col = dynamic_cast<BoxCollider*>(newObject->m_OwnedComponents[i]);
		if (col != nullptr)
		{
			m_Colliders.push_back(col); //오브젝트에서 삭제될때도 월드의 참조를 없애주도록하자. 이런것들은 스마트 포인터를 쓰면 되나? 
			return;
		}
	}
}
