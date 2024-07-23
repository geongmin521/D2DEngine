#include "../D2DEngine/pch.h"
#include "PlayerFSM.h"
#include "Character.h"
#include "../D2DEngine/FiniteStateMachine.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/Animation.h"
#include "../D2DEngine/Movement.h"
#include "../D2DEngine/InputSystem.h"
#include "../D2DEngine/RigidBody.h"

//0번 idle
//1번 run?
//2번 공중돌기?
//3번 공중 발차기
//4번 기어가기
//5번 거미줄 발사후 날라가기
//6번 회전킥
//7번 hit, die// 모션을 똑같이 쓰고 die는 일어나지 못하는걸로하자
//8번 공중에 떠있을때

PlayerFSM::PlayerFSM(FiniteStateMachine* pOwner, std::string Name) : FSMState(pOwner, Name)
{
	ani = m_pOwner->m_pOwner->GetComponent<Animation>();
	move = m_pOwner->m_pOwner->GetComponent<Movement>();
	character = (Character*)m_pOwner->m_pOwner;
}

PlayerFSM::~PlayerFSM()
{

}

void PlayerFSM::EnterState() //상속받은 모든 클래스들이 공통적인 부분을 실행했으면 좋겠는데?
{
}

void PlayerFSM::Update(float DeltaTime)
{
	if (character->alive == false)
	{
		m_pOwner->SetNextState("Die"); //어떠한 상태라도 공중에 있으면 점프상태로
	}
	if (character->isground == false)
	{
		m_pOwner->SetNextState("Jump"); //어떠한 상태라도 공중에 있으면 점프상태로
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
		//디버깅 중일때 델타타입이 커지는게 너무 싫은데 어떻게 하면 고칠수있을까... 
	}
}

void PlayerDie::ExitState()
{
	//객체 파괴하기.. //싱글톤으로 메세지 시스템을 만들고 월드에게 알려주기
}

void PlayerIdle::EnterState()
{

	ani->SetAnimation(0, move->GetVelocity().x > 0 ? false : true);
}

void PlayerIdle::Update(float DeltaTime)
{
	__super::Update(DeltaTime); //공유전이를 위해 업데이트만 모든상태가 부모를 호출?
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
