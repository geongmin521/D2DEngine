#include "../D2DEngine/pch.h"
#include "Character.h"						
#include "../D2DEngine//Animation.h"
#include "../D2DEngine//RigidBody.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/FiniteStateMachine.h"
#include "../D2DEngine/Movement.h"
#include "../D2DEngine/InputSystem.h"
#include "../D2DEngine/D2DRenderer.h"
#include "../D2DEngine/AABB.h"
#include "../D2DEngine/BoxCollider.h"
#include "PlayerFSM.h"

Character::Character()
{
	SetBoundBox(0, 0, 100, 100);
	speed = 10;
	AddComponent(new Animation(L"..\\Data\\spider.png", L"SpiderMan"));
	AddComponent(new RigidBody(m_Transform)); 
	AddComponent(new BoxCollider(m_BoundBox, CollisionType::Block,this)); //m_BoundBox 이것도 애니메이션에서 바꿔주는거아니였나

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
	m_Transform->m_RelativeLocation = { WinHalfSizeX, WinHalfSizeY };//카메라때매 실제 월드 포즈랑 렌더링 포즈랑 다른게 문제임... 
}

Character::~Character()
{

}

void Character::Update(float deltaTime) //자이제 aabb를 본인 사이즈로 처리하리수잇게 만들어야하고.. 
{
	__super::Update(deltaTime);//부모의 업데이트를 한번 호출해야겠지?
	float MoveX = 0;
	float MoveY = 0;
	if (inputSystem->isKey(VK_RIGHT)) 
	{
		MoveX = 1;
	}
	if (inputSystem->isKey(VK_LEFT)) //상태에 재진입을안하는구나
	{
		MoveX = -1;	
	}
	if (inputSystem->isKey(VK_SPACE))
	{
		MoveY = 1;
	}
	GetComponent<Movement>()->SetDirection({ MoveX, MoveY });
}

void Character::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);

	D2DRenderer::GetInstance()->DrawAABB(*m_BoundBox); //얘 박스가 왜 저기있을까? 아 박스도 화면중앙에 올수있게 해줘야하는구나.. 
}

void Character::OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent) //이건 각오브젝트인 각 객체에서 실행하는거아닌가? 
{
	GetComponent<Movement>()->PrevPosition(); //오케이 불러오는건됬고 이제 좌우움직임은 가능하게 하고 위아래 움직임만 무시하면된다.. 
}

void Character::OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
}

void Character::OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
}
