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


//�����´� �������ִٰ�
//�������·� ���ư��� ���� �ٶ󺸱� ����
//���ݻ��¿� ���� �����ӵ��� ���ư���.. 
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

void MissileChase::EnterState() //�����غ��� ���� �θ������ٵ�.. �̰Ŵ� ���� �ٸ� ������ƴ�? 
{
	//�����Ѱ��� ��ũ�ڻ������ϸ� �� ���ͻ����� ������ ����
	MathHelper::Vector2F direction = missile->target->m_RelativeLocation - missile->m_Transform->m_RelativeLocation;
	float dot = missile->dir.Dot(direction); //������ ������ �ֵ��� �������� ��ȣ���� ã������ϰ�.. 
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
	//�̻��� �����ϱ�
}

MissileFSM::MissileFSM(FiniteStateMachine* pOwner, std::string Name) : FSMState(pOwner, Name)
{
	ani = m_pOwner->m_pOwner->GetComponent<Animation>();
	missile = (Missile*)m_pOwner->m_pOwner; //�ٿ�ĳ����
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
