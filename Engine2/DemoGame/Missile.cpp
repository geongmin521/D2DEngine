#include "../D2DEngine/pch.h"
#include "Missile.h"
#include "MissileFSM.h"
#include "../D2DEngine/FiniteStateMachine.h"
#include "../D2DEngine/Animation.h"
#include "../D2DEngine/Movement.h"
#include "../D2DEngine/Transform.h"
Missile::Missile()
{
	distance = 1000;
	Timer = 2;
	AddComponent(new Animation(L"..\\Data\\missile.png", L"Missile"));
	FiniteStateMachine* fsm = new FiniteStateMachine();
	AddComponent(fsm); 
	fsm->CreateState<MissileIdle>("Idle");
	fsm->CreateState<MissileAttack>("Attack");
	fsm->CreateState<MissileChase>("Chase");
	fsm->SetNextState("Idle");
	AddComponent(new Movement(m_Transform, 1000));
	m_Transform->SetRelativeLocation({0,300});
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
}

void Missile::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);
}
