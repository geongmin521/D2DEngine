#include "../D2DEngine/pch.h"
#include "PlayerFSM.h"
#include "../D2DEngine/FiniteStateMachine.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/Animation.h"
#include "../D2DEngine/Movement.h"
#include "../D2DEngine/InputSystem.h"


//#include "../D2DEngine/Transform.h"
//0�� idle
//1�� run?
//2�� ���ߵ���?
//3�� ���� ������
//4�� ����
//5�� �Ź��� �߻��� ���󰡱�
//6�� ȸ��ű
//7�� hit, die// ����� �Ȱ��� ���� die�� �Ͼ�� ���ϴ°ɷ�����
//8�� ���߿� ��������

//�׳� �÷��̾ ����ְ� �÷��̾��� ���¿����� fsm�� ���� ��Ű�°� �ξ� ���������ִٴ� �����̵��.. 
//���´� �׳� �ִϸ��̼� ����������� �����ϰ� ������ �ξ� ������ҰŰ�����.. 

PlayerFSM::PlayerFSM(FiniteStateMachine* pOwner, std::string Name) : FSMState(pOwner, Name)
{
	ani = m_pOwner->m_pOwner->GetComponent<Animation>();
	move = m_pOwner->m_pOwner->GetComponent<Movement>();
}

PlayerFSM::~PlayerFSM()
{

}

void PlayerAttack::EnterState() //���� ���س��� ����ȭ�� �����ϴ�.. 
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
	ani->SetAnimation(1, move->GetDirection().x > 0 ? false : true);
}

void PlayerRun::Update(float DeltaTime)
{
	ani->SetMirror(move->GetDirection().x > 0 ? false : true); //������ٺ���  getter����
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
	ani->SetAnimation(7, move->GetDirection().x > 0 ? false : true);
}

void PlayerDie::Update(float DeltaTime)
{
	if (ani->IsEnd() == true)
	{
		m_pOwner->SetNextState("");
	}
}

void PlayerDie::ExitState()
{
	//��ü �ı��ϱ�.. //�ٵ��̰� �������� ��ȣ�� �����.. �̸� ��� �ϸ�˸���..
	//�̰͵� �޼����� �������� ó���Ҽ��ְڳ�.. 
}
//�̰� �ҷ��� �ִϸ��̼Ǻ��� �غ� �Ǿ����.. 
void PlayerIdle::EnterState()
{
	ani->SetAnimation(0, move->GetDirection().x > 0 ? false : true);
}

void PlayerIdle::Update(float DeltaTime)
{
	Movement* move = m_pOwner->m_pOwner->GetComponent<Movement>();

	if (move->GetDirection() != MathHelper::Vector2F(0,0)) //���� ���ǵ�� �ѻ� �����ϰ� ���⸸���� �Ǻ��ϰ��־���.. 
	{
		//�ӵ��� �̵����� �ƴ��� �Ǵ��Ҽ��ְ�.. 
		// y �𷺼��� ������ ���������� �ƴ��� �Ǵܰ���
		if (move->GetDirection().y != 0) //�÷��̴ϱ� 0 ���� �ϸ� �ȵɼ���?
		{
			m_pOwner->SetNextState("Jump");
		}
		else
		{
			m_pOwner->SetNextState("Run");
			
		}	
	}
	else if (inputSystem->isKeyDown('A'))
	{
		m_pOwner->SetNextState("Attack");
	}
}

void PlayerIdle::ExitState() 
{
}

void PlayerJump::EnterState()
{
	ani->SetAnimation(2, move->GetDirection().x > 0 ? false : true);
} 

void PlayerJump::Update(float DeltaTime)
{
	//float jumpDir = m_pOwner->m_pOwner->GetComponent<Movement>()->GetDirection().y;
	//if (jumpDir == -1)
	//	m_pOwner->SetNextState("Idle");
	//jumpDir -= DeltaTime * 10;
	//m_pOwner->m_pOwner->GetComponent<Movement>()->SetDirection({ 0,jumpDir });

}

void PlayerJump::ExitState() //������ �ٵ� ���ؼ� �������Ű�..�����Ʈ�� ������ٵ� ���� �̵����ٸ��� ó���Ǵ°Ű�.. 
{

}