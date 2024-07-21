#include "../D2DEngine/pch.h"
#include "PlayerFSM.h"
#include "Character.h"
#include "../D2DEngine/FiniteStateMachine.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/Animation.h"
#include "../D2DEngine/Movement.h"
#include "../D2DEngine/InputSystem.h"



//#include "../D2DEngine/Transform.h"
//0번 idle
//1번 run?
//2번 공중돌기?
//3번 공중 발차기
//4번 기어가기
//5번 거미줄 발사후 날라가기
//6번 회전킥
//7번 hit, die// 모션을 똑같이 쓰고 die는 일어나지 못하는걸로하자
//8번 공중에 떠있을때

//그냥 플레이어를 들고있고 플레이어의 상태에따라 fsm을 전이 시키는게 훨씬 나을수도있다는 생각이드네.. 
//상태는 그냥 애니메이션 관리정도라고 생각하고 권한을 훨씬 낮춰야할거같은데.. 

PlayerFSM::PlayerFSM(FiniteStateMachine* pOwner, std::string Name) : FSMState(pOwner, Name)
{
	ani = m_pOwner->m_pOwner->GetComponent<Animation>();
	move = m_pOwner->m_pOwner->GetComponent<Movement>();
	character = (Character*)m_pOwner->m_pOwner;
}

PlayerFSM::~PlayerFSM()
{

}

void PlayerAttack::EnterState() //오늘 다해놔야 최적화가 가능하다.. 
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
	ani->SetMirror(move->GetVelocity().x > 0 ? false : true); //멤버접근보다  getter쓰자
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
	//객체 파괴하기.. //근데이건 월드한테 신호를 줘야함.. 이를 어떻게 하면알릴까..
	//이것도 메세지의 일종으로 처리할수있겠네.. 
}
//이거 할려면 애니메이션부터 준비가 되어야함.. 
void PlayerIdle::EnterState()
{
	ani->SetAnimation(0, move->GetVelocity().x > 0 ? false : true);
}

void PlayerIdle::Update(float DeltaTime)
{
	Movement* move = m_pOwner->m_pOwner->GetComponent<Movement>();
		//속도로 이동중인 아닌지 판단할수있고.. 
		// y 디렉션의 값으로 점프중인지 아닌지 판단가능
	if (character->isground == false) //플롯이니까 0 으로 하면 안될수도? //isblock의 이전과 이후로 땅인지아닌지도 판단가능? 
		//이전위치의로 갈때 현재위치와의 높이차이로 위에서 충돌한건지 아래에서 충돌한건지 확인가능
	{
		m_pOwner->SetNextState("Jump");
		move->isGravity = true;//밑에 바닥이있는지 없는지 계속 검사해야하나? 
	}
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
} 

void PlayerJump::Update(float DeltaTime)
{
	//축으로 이동했다고 콜라이더 처리가 오면.. 점프를 그만뒤야하는거지?
	//float jumpDir = m_pOwner->m_pOwner->GetComponent<Movement>()->GetDirection().y;
	//if (jumpDir == -1)
	//	m_pOwner->SetNextState("Idle");
	//jumpDir -= DeltaTime * 10;
	//m_pOwner->m_pOwner->GetComponent<Movement>()->SetDirection({ 0,jumpDir });
	if (character->isground == true)
	{
		m_pOwner->SetNextState("Idle");
		//move->isGravity = false;
	}
}

void PlayerJump::ExitState() //리지드 바디에 의해서 떨어질거고..무브먼트와 리지드바디에 의한 이동은다르게 처리되는거고.. 
{

}
