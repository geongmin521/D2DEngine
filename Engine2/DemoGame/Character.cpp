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
#include "PlayerFSM.h" //아따 헤더파일도 참 많구만.. 

Character::Character()
{
	SetBoundBox(0, 0, 100, 100);
	speed = 300;
	Jumpspeed = 500;
	AddComponent(new Animation(L"..\\Data\\spider.png", L"SpiderMan"));//컴포넌트들을 계속 순회하면서 찾지않게 
	//멤버 변수로 들고있기.. 
	AddComponent(new RigidBody()); 
	AddComponent(new BoxCollider(m_BoundBox, CollisionType::Block,this, CollisionLayer::Player)); 

	AddComponent(new Movement(m_Transform ,true)); 
	FiniteStateMachine* fsm = new FiniteStateMachine();
	AddComponent(fsm); 
	fsm->CreateState<PlayerIdle>("Idle");
	fsm->CreateState<PlayerAttack>("Attack");
	fsm->CreateState<PlayerHit>("Hit");
	fsm->CreateState<PlayerDie>("Die");
	fsm->CreateState<PlayerRun>("Run");
	fsm->CreateState<PlayerJump>("Jump");

	fsm->SetNextState("Idle"); 
	renderOrder = 100; 
	m_Transform->m_RelativeScale = { 3,3 };
	m_Transform->m_RelativeLocation = { WinHalfSizeX, WinHalfSizeY };
}

Character::~Character()
{

}

void Character::Update(float deltaTime)
{
	isBlock[0] = false; 
	isBlock[1] = false;
	
	float MoveX = 0;

	if (inputSystem->isKey(VK_RIGHT)) 
	{
		MoveX = 1 * speed;

	}
	if (inputSystem->isKey(VK_LEFT)) 
	{
		MoveX = -1 * speed;	
	}
	if (inputSystem->isKeyDown(VK_SPACE) && isground )
	{
		isground = false;
		Jump();
	}

	if(isground) 
		GetComponent<RigidBody>()->setActive(false);
	MoveY += GetComponent<RigidBody>()->getGravity();
 	GetComponent<Movement>()->SetVelocity({ MoveX,  MoveY });

	__super::Update(deltaTime);
}

void Character::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);
	D2DRenderer::GetInstance()->DrawTextFunc(std::to_wstring(GetComponent<Movement>()->GetVelocity().x) , 0, 0);
	D2DRenderer::GetInstance()->DrawTextFunc(std::to_wstring(isBlock[0]) , 0, 100);
	D2DRenderer::GetInstance()->DrawTextFunc(std::to_wstring(isBlock[1]) , 0, 200);
	D2DRenderer::GetInstance()->DrawAABB(*m_BoundBox); 
}

void Character::Jump()
{
	MoveY = -1 * Jumpspeed;
	GetComponent<RigidBody>()->setActive(true);
}

void Character::OnBlock(Collider* pOtherComponent) //박스콜라이더였으면 컴포넌트를 상속받아서 알수잇을텐데.. 
{
	//콜라이더가 그냥 컴포넌트를 상속받으면안되나? 일관되게 컨트롤할수있긴한데.. //아님 걍 레이어로 가져올까? .. 
	if (pOtherComponent->GetCollisionLayer() == CollisionLayer::Missile) //충돌레이어를 바로 넣어줄까? 충돌한 물체가 어떤물체인지 알수가없네.. 
	{
		//다이를 전해줘야하는데.. 공유전이이기도하고.. 여기서 바로 바꿔줘도 되나? 
		GetComponent<FiniteStateMachine>()->SetNextState("Die");//모든 오브젝트생성을 일관되게 만들수있을려면.. 
		//팩토리가 있어야겠지? 
	}
	AABB prevXBox = *m_BoundBox, prevYBox = *m_BoundBox; 
	prevXBox.m_Center.x = GetComponent<Movement>()->GetPrevPos().x;	
	prevYBox.m_Center.y = GetComponent<Movement>()->GetPrevPos().y; 
	isBlock[0] = !pOtherComponent->IsCollide(&prevXBox);
	isBlock[1] = !pOtherComponent->IsCollide(&prevYBox); 
	if (isBlock[1] == true && m_Transform->m_RelativeLocation.y > GetComponent<Movement>()->GetPrevPos().y)
	{
		isground = true;
	}
	else if (isBlock[1] == true && m_Transform->m_RelativeLocation.y < GetComponent<Movement>()->GetPrevPos().y)
	{
		//위쪽에서 부딪힌거임.. 
		GetComponent<Movement>()->SetVelocity({0,0});
	}
	GetComponent<Movement>()->PrevPosition(isBlock[0], isBlock[1]); 

}

void Character::OnBeginOverlap(Collider* pOtherComponent)
{
}

void Character::OnEndOverlap(Collider* pOtherComponent)
{
}
