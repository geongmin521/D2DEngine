#include "../D2DEngine/pch.h"
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

void MissileChase::EnterState()
{
	D2D_VECTOR_2F dir = missile->target->m_RelativeLocation - missile->m_Transform->m_RelativeLocation;
	// �� ���� �ȵ�°� �ʹ� ���� �ؾ��Ұ͵� �ʹ� ������? 
	missile->m_Transform->AddRelativeRotation(30); //�÷��̾ �ٶ󺸴� ������ ������
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
