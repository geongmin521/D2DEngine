#include "../D2DEngine/pch.h"
#include "PlayerFSM.h"
#include "Character.h"
#include "../D2DEngine/FiniteStateMachine.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/Animation.h"
#include "../D2DEngine/Movement.h"
#include "../D2DEngine/InputSystem.h"
#include "../D2DEngine/RigidBody.h"

//0�� idle
//1�� run?
//2�� ���ߵ���?
//3�� ���� ������
//4�� ����
//5�� �Ź��� �߻��� ���󰡱�
//6�� ȸ��ű
//7�� hit, die// ����� �Ȱ��� ���� die�� �Ͼ�� ���ϴ°ɷ�����
//8�� ���߿� ��������

PlayerFSM::PlayerFSM(FiniteStateMachine* pOwner, std::string Name) : FSMState(pOwner, Name)
{
	ani = m_pOwner->m_pOwner->GetComponent<Animation>();
	move = m_pOwner->m_pOwner->GetComponent<Movement>();
	character = (Character*)m_pOwner->m_pOwner;
}

PlayerFSM::~PlayerFSM()
{

}

void PlayerFSM::EnterState() //��ӹ��� ��� Ŭ�������� �������� �κ��� ���������� ���ڴµ�?
{
}

void PlayerFSM::Update(float DeltaTime)
{
	if (character->alive == false)
	{
		m_pOwner->SetNextState("Die"); //��� ���¶� ���߿� ������ �������·�
	}
	if (character->isground == false)
	{
		m_pOwner->SetNextState("Jump"); //��� ���¶� ���߿� ������ �������·�
	}
}

void PlayerFSM::ExitState()
{
}

void PlayerAttack::EnterState() 
{
	ani->SetAnimation(6, false); 
	ani->isLoop = false;
}

void PlayerAttack::Update(float DeltaTime)
{
	bool isend = ani->IsEnd();
	if (isend)
		m_pOwner->SetNextState("Idle");
	
}

void PlayerAttack::ExitState()
{
	
}

void PlayerHit::EnterState()
{
	ani->SetAnimation(7, false); 
}	

void PlayerHit::Update(float DeltaTime)
{
	if (ani->IsEnd())
		m_pOwner->SetNextState("Idle");
}

void PlayerHit::ExitState()
{
	
}

void PlayerRun::EnterState()
{
	ani->SetAnimation(1, move->GetVelocity().x > 0 ? false : true);
}

void PlayerRun::Update(float DeltaTime)
{
	__super::Update(DeltaTime);
	ani->SetMirror(move->GetVelocity().x > 0 ? false : true);
	if (!inputSystem->isKey(VK_LEFT) && !inputSystem->isKey(VK_RIGHT))
	{
		m_pOwner->SetNextState("Idle");
	}
}

void PlayerRun::ExitState()
{
}

void PlayerDie::EnterState()
{
	ani->SetAnimation(7, move->GetVelocity().x > 0 ? false : true);
	ani->isLoop = false;
}

void PlayerDie::Update(float DeltaTime)
{
	if (ani->IsEnd() == true)
	{
		//����� ���϶� ��ŸŸ���� Ŀ���°� �ʹ� ������ ��� �ϸ� ��ĥ��������... 
	}
}

void PlayerDie::ExitState()
{
	//��ü �ı��ϱ�.. //�̱������� �޼��� �ý����� ����� ���忡�� �˷��ֱ�
}

void PlayerIdle::EnterState()
{

	ani->SetAnimation(0, move->GetVelocity().x > 0 ? false : true);
}

void PlayerIdle::Update(float DeltaTime)
{
	__super::Update(DeltaTime); //�������̸� ���� ������Ʈ�� �����°� �θ� ȣ��?
	if(move->GetVelocity().x != 0)
	{
		m_pOwner->SetNextState("Run");
	}		
	if (inputSystem->isKeyDown('A'))
	{
		m_pOwner->SetNextState("Attack");
	}
}

void PlayerIdle::ExitState() 
{
}

void PlayerJump::EnterState()
{
	ani->SetAnimation(2, move->GetVelocity().x > 0 ? false : true);
	doublejump = true;
	doublejumpTimer = 0.5; 
} 

void PlayerJump::Update(float DeltaTime)
{
	doublejumpTimer -= DeltaTime;
	if (character->isground == true)
	{
		m_pOwner->SetNextState("Idle");
		move->isGravity = false;
	}
	else
	{
		move->isGravity = true;
	}
	if (doublejump == true && inputSystem->isKeyDown(VK_SPACE)&& doublejumpTimer<0) 
	{
		character->GetComponent<RigidBody>()->resetGravity();
		doublejump = false;
		character->Jump();
	}
}

void PlayerJump::ExitState()
{

}
