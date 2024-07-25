#include "../D2DEngine/pch.h"
#include "PlayerFSM.h"
#include "Character.h"
#include "SpiderWeb.h"
#include "../D2DEngine/FiniteStateMachine.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/Animation.h"
#include "../D2DEngine/Movement.h"
#include "../D2DEngine/InputSystem.h"
#include "../D2DEngine/RigidBody.h"
#include "../D2DEngine/Transform.h"

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
	if (!inputSystem->isKey('A') && !inputSystem->isKey('D'))
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
	__super::Update(DeltaTime); 
	if(move->GetVelocity().x != 0)
	{
		m_pOwner->SetNextState("Run");
	}		
	if (inputSystem->isKeyDown('F'))
	{
		m_pOwner->SetNextState("Attack");
	}
}

void PlayerIdle::ExitState() 
{
	//character->m_pOwner.de
}

void PlayerJump::EnterState()
{
	character->GetComponent<RigidBody>()->resetGravity();
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

PlayerShared::PlayerShared(FiniteStateMachine* pOwner, std::string Name) : PlayerFSM(pOwner, Name)
{
	pOwner->SetSharedTransition(this);
}

void PlayerShared::EnterState()
{
}

void PlayerShared::Update(float DeltaTime)
{
	if (character->alive == false )
	{
		m_pOwner->SetNextState("Die"); 
	}
	if (character->isground == false && character->ishanging == false)
	{
		m_pOwner->SetNextState("Jump"); 
	}
	if (character->ishanging == true)
	{
		m_pOwner->SetNextState("Hanging"); 
	}
}

void PlayerShared::ExitState()
{
}

void PlayerHanging::EnterState()
{
	character->m_Transform->SetRelativeLocation({ 0,200 }); //위치를 거미줄 밑으로 초기화
	move->m_PrevRelativeLocation ={ 0,0 };
	character->m_Transform->SetParent(character->web->m_Transform); //부모설정하기 
	character->GetComponent<RigidBody>()->setActive(false); 
	character->MoveY =0; 
	SwingSpeed = 50;

	character->m_Transform->Update(1);
	ani->SetAnimation(2, move->GetVelocity().x > 0 ? false : true);
}

void PlayerHanging::Update(float DeltaTime)
{
	if (character->ishanging == false)
	{
		m_pOwner->SetNextState("Jump");
	}
	float sin = std::sinf(timer);
	if (inputSystem->isKey('D'))
	{
		if (sin < 0)
			SwingSpeed += DeltaTime * 20;
	}
	else if (inputSystem->isKey('A'))
	{
		if(sin > 0)
			SwingSpeed += DeltaTime * 20;
	}
	else
	{
		if(SwingSpeed > 0)
			SwingSpeed -= DeltaTime * 10;
	}
	move->m_PrevRelativeLocation = character->m_Transform->GetWorldLocation();
	timer += DeltaTime;
	float angleChange = sin * 0.5f * SwingSpeed;
	character->web->m_Transform->SetRelativeRotation(angleChange); 
}

void PlayerHanging::ExitState()
{
	character->GetComponent<RigidBody>()->setActive(true);	
	character->m_Transform->SetParent(nullptr);				//부모끊어주기
	character->m_Transform->SetRelativeLocation(character->GetWorldLocation());
	character->m_Transform->SetRelativeRotation(0);
	character->ishanging = false;
}
