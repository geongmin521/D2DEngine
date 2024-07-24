#include "../D2DEngine/pch.h"
#include "../D2DEngine/MathHelper.h"
#include "MissileFSM.h"
#include "Missile.h"
#include "../D2DEngine/FiniteStateMachine.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/Animation.h"
#include "../D2DEngine/Movement.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/InputSystem.h"


//대기상태는 가만히있다가
//추적상태로 돌아가면 적을 바라보기 시작
//공격상태에 들어가면 빠른속도로 날아가기.. 
void MissileIdle::EnterState()
{
}

void MissileIdle::Update(float DeltaTime)
{
	if (missile->distance < 500)
	{
		m_pOwner->SetNextState("Chase");
	}
}

void MissileIdle::ExitState()
{
}

void MissileChase::EnterState() //생각해보니 각자 부모가있을텐데.. 이거는 서로 다른 각도들아님? 
{
	//내적한값의 아크코사인을하면 두 벡터사이의 각도가 나옴
	MathHelper::Vector2F direction = missile->target->m_RelativeLocation - missile->m_Transform->m_RelativeLocation;
	float dot = missile->dir.Dot(direction); //방향이 왼쪽인 애들은 외적으로 부호까지 찾아줘야하고.. 
	dot /= direction.Length();
	float acos = std::acosf(dot) * 180.0 / PI; 
	missile->m_Transform->AddRelativeRotation(acos);
	missile->dir = direction.Normalize(); 
}

void MissileChase::Update(float DeltaTime)
{
	missile->Timer -= DeltaTime;
	if(missile->Timer<0)
		m_pOwner->SetNextState("Attack");

}

void MissileChase::ExitState()
{
}

void MissileAttack::EnterState() 
{
	missile->speed = 1000;
 	m_pOwner->m_pOwner->GetComponent<Movement>()->SetVelocity({ missile->dir.x * missile->speed, missile->dir.y * missile->speed });
}

void MissileAttack::Update(float DeltaTime)
{

}

void MissileAttack::ExitState()
{
	//미사일 삭제하기
}

MissileFSM::MissileFSM(FiniteStateMachine* pOwner, std::string Name) : FSMState(pOwner, Name)
{
	ani = m_pOwner->m_pOwner->GetComponent<Animation>();
	missile = (Missile*)m_pOwner->m_pOwner; //다운캐스팅
}

MissileFSM::~MissileFSM()
{
}

MissileShared::MissileShared(FiniteStateMachine* pOwner, std::string Name) : MissileFSM(pOwner, Name) 
{
	pOwner->SetSharedTransition(this);
}

void MissileShared::EnterState()
{
}

void MissileShared::Update(float DeltaTime)
{
}

void MissileShared::ExitState()
{
}
