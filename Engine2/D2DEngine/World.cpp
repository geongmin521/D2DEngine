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
	m_CullingBoundDefault->SetExtent(width/2, height/2);
	m_CullingBoundDefault->SetCenter(0,0);
	SetCullingBound(m_CullingBoundDefault);	
}

World::~World()
{

}


void World::Update(float deltaTime)
{
	if (m_Remove.size() != 0)
		removeElements(m_GameObjects, m_Remove);
	for (auto& obj : m_GameObjects) 
	{
		if (!obj->isActive)
			continue;
		obj->Update(deltaTime);
	}
	
	CollisionManager::GetInstance()->CollisionCheck();
}

void World::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	for (auto& obj : m_GameObjects) 
	{		
		if (!obj->isActive)
			continue;
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

void World::removeElements(std::list<GameObject*>& origin, const std::list<GameObject*>& remove) {
	for (auto it = remove.begin(); it != remove.end(); ++it) {
		origin.remove(*it); // 첫 번째 리스트에서 두 번째 리스트의 요소 제거
	}
}

void World::DeleteGameObject(GameObject* gameObject)//지워질 객체를 그냥 미리 담아놓고 업데이트 돌기전에 처리하자
{
	m_Remove.push_back(gameObject);
}
