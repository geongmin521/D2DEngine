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

Character::Character(): speed(300), Jumpspeed(500)
{

	SetBoundBox(0, 0, 100, 100); 
	AddComponent(new Animation(L"..\\Data\\spider.png", L"SpiderMan"));
	AddComponent(new RigidBody()); 
	AddComponent(new BoxCollider(m_BoundBox, CollisionType::Block,this, CollisionLayer::Player)); 
	AddComponent(new Movement(m_Transform)); 
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

void Character::Update(float deltaTime) //Ŀ�ǵ� �����̳� ��Ÿ �޼��� �ý��۵�� �̷���������� �����ϴµ�.. ��.. 
{
	float MoveX = 0;
	if (alive)
	{
		if (ishanging == false)
		{
			if (inputSystem->isKey('D')) //Ű�Է¸� ���ް��ϸ�ǳ�? 
			{
				MoveX = 1 * speed;
			}
			if (inputSystem->isKey('A'))
			{
				MoveX = -1 * speed;
			}
		}
		
		if (inputSystem->GetMouseButtonDown(0) && ishanging ==false)
		{
			web->isActive = true; //�̰͵� getter setter ������
			web->m_Transform->SetRelativeLocation(m_Transform->GetWorldLocation());
			MathHelper::Vector2F dir = inputSystem->GetMouseState().GetMousePos() - m_Transform->GetWorldLocation();
			web->Fire(dir); //wasd�� �����̸� �����̹ٷ� ���� ���콺�� �߻�? ���� //���콺 �����ǰ� �÷��̾��� ��ġ�� ���⸸ ��������. 
		}
		if (inputSystem->GetMouseButtonDown(2) && ishanging == true)
		{
			ishanging = false;
			isground = true;
			web->isActive = false;
		}
		if (inputSystem->isKeyDown(VK_SPACE) && isground)//�̰Ŵ� ��¥ ���� �ȳ����ҷ��� Ŀ�ǵ� �������νϴ� �ٲ�߰ڴ� 
			//�����
		{
			isground = false;
			Jump();
		}
	}

	MoveY += GetComponent<RigidBody>()->getGravity();
 	GetComponent<Movement>()->SetVelocity({ MoveX,  MoveY });

	__super::Update(deltaTime);
}

void Character::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);	
	//D2DRenderer::GetInstance()->DrawTextFunc(m_Transform->ShowPos(), 0, 0);
	D2DRenderer::GetInstance()->DrawAABB(*m_BoundBox); 
}

void Character::Jump()
{
	MoveY = -1 * Jumpspeed;
}

void Character::OnBlock(Collider* pOtherComponent)
{
	if (pOtherComponent->GetCollisionLayer() == CollisionLayer::Missile) //������ġ�� 
	{
		alive = false;
	}
	else if (pOtherComponent->GetCollisionLayer() == CollisionLayer::Platform)
	{
		AABB prevXBox = *m_BoundBox, prevYBox = *m_BoundBox; 
		prevXBox.Center.x = GetComponent<Movement>()->GetPrevPos().x;
		prevYBox.Center.y = GetComponent<Movement>()->GetPrevPos().y;
		bool isBolckX = !pOtherComponent->IsCollide(&prevXBox);
		bool isBolckY = !pOtherComponent->IsCollide(&prevYBox);
		bool isUpside = m_Transform->m_RelativeLocation.y < GetComponent<Movement>()->GetPrevPos().y;
		if (isBolckY == true)
		{
			if (isUpside)
			{
				GetComponent<Movement>()->SetVelocity({ 0,0 });
			}
			else
			{
				GetComponent<RigidBody>()->resetGravity();
				isground = true;
				MoveY = 0;
			}			
		}
		GetComponent<Movement>()->PrevPosition(isBolckX, isBolckY);
	}
}

void Character::OnBeginOverlap(Collider* pOtherComponent)
{
}

void Character::OnEndOverlap(Collider* pOtherComponent)
{
}
