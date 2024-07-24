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
	__super::Update(DeltaTime); //공유전이를 위해 업데이트만 모든상태가 부모를 호출?
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

PlayerShared::PlayerShared(FiniteStateMachine* pOwner, std::string Name) : PlayerFSM(pOwner, Name)
{
	pOwner->SetSharedTransition(this);
}

void PlayerShared::EnterState()
{
}

void PlayerShared::Update(float DeltaTime)
{
	if (character->alive == false)
	{
		m_pOwner->SetNextState("Die"); //어떠한 상태라도 공중에 있으면 점프상태로
	}
	if (character->isground == false)
	{
		m_pOwner->SetNextState("Jump"); //어떠한 상태라도 공중에 있으면 점프상태로
	}
	if (character->web->getAttach() == true)
	{
		m_pOwner->SetNextState("Hanging"); //어떠한 상태라도 공중에 있으면 점프상태로
	}
}

void PlayerShared::ExitState()
{
}

void PlayerHanging::EnterState()
{
	//부모설정을 웹에서하지말고 여기서하자 //스케일차이도 상관있나?
	character->m_Transform->SetRelativeLocation({ 0,100 }); //왜 절대좌표가 엄청나게 늘어나는데? 
	move->m_PrevRelativeLocation ={ 0,0 }; //왜 절대좌표가 엄청나게 늘어나는데? 
	//부모위치는인정인데 왜지?
	character->m_Transform->SetParent(character->web->m_Transform); //부모설정하기 
	character->GetComponent<RigidBody>()->setActive(false); //해줘야하는 설정이 엄청많구만
	character->m_Transform->Update(1);
	//역시 부모로 설정하면서 문제가 많아지는구만.. 
	//상대좌표가 월드좌표였는데 이걸 수정해줘야지
	character->ishanging = true;
}

void PlayerHanging::Update(float DeltaTime)
{
	//스파이더웹과의 거리가 정해진 거리가될때까지 이동하기
	//또한 좌우 이동시 웹의 회전으로만 처리하기./.

	if (inputSystem->isKey('D')) //키입력만 못받게하면되나? //회전운동으로 벽을 뚫지않게해야하는데 흠.. 
	{
		character->web->m_Transform->AddRelativeRotation(SwingSpeed * DeltaTime);
	}
	if (inputSystem->isKey('A'))
	{
		character->web->m_Transform->AddRelativeRotation(-SwingSpeed * DeltaTime);
	}
	//플레이어 입력 즉 커멘드가 덮어씌워져야하는데 이걸 커맨드 패턴으로 처리하는게 제일 깔끔하지만
	//시간이 없기때문에 bool 값하나로 관리할까 고민중.. 
}

void PlayerHanging::ExitState()
{
	//아 근데 부모를 썼다가 끊으면 위치 문제가좀 생길거같은데 어떻게 초기화를 잘해주면 괜찮아질려나? 
	character->m_Transform->SetParent(nullptr); //부모끊어주기
	character->m_Transform->SetRelativeLocation(character->GetWorldLocation());
	character->ishanging = false;
}
