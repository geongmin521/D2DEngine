#include "../D2DEngine/pch.h"
#include "Missile.h"
#include "MissileFSM.h"
#include "../D2DEngine/FiniteStateMachine.h"
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
	__super::Update(deltaTime);//아 얘는 또 월드의 통제를 안받으니까.. 콜라이더 계산을 못하는구나.. 싱글톤으로 매니저를 빨리만들까? 
	distance = sqrt(
		pow((m_Transform->GetWorldLocation().x - target->GetWorldLocation().x), 2) +
		pow((m_Transform->GetWorldLocation().y - target->GetWorldLocation().y), 2));
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
