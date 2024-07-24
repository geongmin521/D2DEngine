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
#include "SpiderWeb.h" 

Character::Character()
{

	SetBoundBox(0, 0, 100, 100); //자식관계가 역전되는게 가능할까?
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
	fsm->CreateState<PlayerShared>("Shared");
	fsm->CreateState<PlayerHanging>("Hanging");

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
	if (alive)
	{
		if (ishanging == false)
		{
			if (inputSystem->isKey('D')) //키입력만 못받게하면되나? 
			{
				MoveX = 1 * speed;
			}
			if (inputSystem->isKey('A'))
			{
				MoveX = -1 * speed;
			}
		}
		
		if (inputSystem->GetMouseButtonDown(0))
		{
			web->isActive = true; //이것도 getter setter 만들자
			web->m_Transform->SetRelativeLocation(m_Transform->GetWorldLocation());
			MathHelper::Vector2F dir = inputSystem->GetMouseState().GetMousePos() - m_Transform->GetWorldLocation();
			web->Fire(dir); //wasd로 움직이며 스페이바로 점프 마우스로 발사? ㅇㅋ //마우스 포지션과 플레이어의 위치로 방향만 보내주자. 
		}
		if (inputSystem->isKeyDown(VK_SPACE) && isground)
		{
			isground = false;
			Jump();
		}
	}


	if (isground)
	{
		GetComponent<RigidBody>()->setActive(false);
		MoveY = 0;
	}
		
	MoveY += GetComponent<RigidBody>()->getGravity();
 	GetComponent<Movement>()->SetVelocity({ MoveX,  MoveY });

	__super::Update(deltaTime);
}

void Character::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);
	
	D2DRenderer::GetInstance()->DrawTextFunc(m_Transform->ShowPos(), 0, 0);

	D2DRenderer::GetInstance()->DrawAABB(*m_BoundBox); 
}

void Character::Jump()
{
	MoveY = -1 * Jumpspeed;
	GetComponent<RigidBody>()->setActive(true);
}

void Character::OnBlock(Collider* pOtherComponent)
{
	if (pOtherComponent->GetCollisionLayer() == CollisionLayer::Missile) //이전위치도 
	{
		//alive = false;
	}
	else if (pOtherComponent->GetCollisionLayer() == CollisionLayer::Platform)
	{
		AABB prevXBox = *m_BoundBox, prevYBox = *m_BoundBox;  //여기 정리하자. 이제 거미줄을 쏴야하는데
		//플레이어가 들고있어야할거고 
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
			GetComponent<Movement>()->SetVelocity({ 0,0 });
		}
		GetComponent<Movement>()->PrevPosition(isBlock[0], isBlock[1]);
	}
}

void Character::OnBeginOverlap(Collider* pOtherComponent)
{
}

void Character::OnEndOverlap(Collider* pOtherComponent)
{
}
