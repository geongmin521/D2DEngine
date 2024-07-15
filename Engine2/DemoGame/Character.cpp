#include "../D2DEngine/pch.h"
#include "Character.h"						
#include "../D2DEngine//Animation.h"
#include "../D2DEngine//RigidBody.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/FiniteStateMachine.h"
#include "../D2DEngine/Movement.h"
#include "../D2DEngine/InputSystem.h"
#include "PlayerFSM.h"

Character::Character()
{
	SetBoundBox(0, 0, 100, 100);
	speed = 10;
	AddComponent(new Animation(L"..\\Data\\spider.png", L"SpiderMan"));
	AddComponent(new RigidBody(m_Transform)); 

	AddComponent(new Movement(m_Transform , 200)); //이제 방향만 지정해주면되겠네..
	FiniteStateMachine* fsm = new FiniteStateMachine();
	//교수님이 원하는건 각 캐릭터마다 fsm을 새로만들어서 상속받아서 재정의하고
	//그걸 넣어줘야하는건가? protected로 생성할려면 그게 맞나보네. 
	AddComponent(fsm); //오케이 잘떨어지고.. 
	fsm->CreateState<PlayerIdle>("Idle");
	fsm->CreateState<PlayerAttack>("Attack");
	fsm->CreateState<PlayerHit>("Hit");
	fsm->CreateState<PlayerDie>("Die");
	fsm->CreateState<PlayerRun>("Run");
	fsm->CreateState<PlayerJump>("Jump");
	fsm->SetNextState("Idle"); 
	//플레이어의 fsm 컴포넌트를 넣어주고.. 
	renderOrder = 100; 
	m_Transform->m_RelativeScale = { 3,3 };
}

Character::~Character()
{

}

void Character::Update(float deltaTime) //자이제 aabb를 본인 사이즈로 처리하리수잇게 만들어야하고.. 
{
	__super::Update(deltaTime);//부모의 업데이트를 한번 호출해야겠지?
}

void Character::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);
}
