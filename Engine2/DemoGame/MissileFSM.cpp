#include "../D2DEngine/pch.h"
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

void MissileChase::EnterState()
{
	missile->m_Transform->AddRelativeRotation(30); //플레이어를 바라보는 각도를 구하자
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

void MissileAttack::EnterState() //키가 다른게 눌렸는데도 눌려져있어서 안되는 버그확인
{
	//각도만 가지고 벡터로 변환해야하는데.. 
	missile->GetComponent<Movement>()->SetDirection({1,-0.3f});
	missile->GetComponent<Movement>()->SetSpeed(1000);
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
