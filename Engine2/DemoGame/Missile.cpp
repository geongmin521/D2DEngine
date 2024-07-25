#include "../D2DEngine/pch.h"
#include "Missile.h"
#include "MissileFSM.h"
#include "../D2DEngine/FiniteStateMachine.h"
#include "../D2DEngine/World.h"
#include "../D2DEngine/Animation.h"
#include "../D2DEngine/Movement.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/BoxCollider.h"

Missile::Missile()
{
	distance = 1000;
	Timer = 2;
	AddComponent(new Animation(L"..\\Data\\missile.png", L"Missile"));
	AddComponent(new BoxCollider(m_BoundBox, CollisionType::Block, this,CollisionLayer::Missile));
	FiniteStateMachine* fsm = new FiniteStateMachine();
	AddComponent(fsm); 
	fsm->CreateState<MissileIdle>("Idle");
	fsm->CreateState<MissileAttack>("Attack");
	fsm->CreateState<MissileChase>("Chase");
	fsm->CreateState<MissileShared>("Chase");
	fsm->SetNextState("Idle");
	AddComponent(new Movement(m_Transform));
	m_Transform->SetRelativeLocation({0,300});
	dir = { 0,-1 };
}

Missile::~Missile()
{
}

void Missile::Update(float deltaTime)
{
	__super::Update(deltaTime);
	distance = sqrt(
		pow((m_Transform->GetWorldLocation().x - target->GetWorldLocation().x), 2) +
		pow((m_Transform->GetWorldLocation().y - target->GetWorldLocation().y), 2));

	if (m_Transform->GetWorldLocation().y < 0|| m_Transform->GetWorldLocation().y > WinSizeY) //화면밖이면 지우기
	{
		m_pOwner->DeleteGameObject(this);
	}
}

void Missile::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);
}

void Missile::OnBlock(Collider* pOtherComponent)
{
	//if()
}

void Missile::OnBeginOverlap(Collider* pOtherComponent)
{
}

void Missile::OnEndOverlap(Collider* pOtherComponent)
{
}
