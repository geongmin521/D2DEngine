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

	AddComponent(new Movement(m_Transform , 200)); //���� ���⸸ �������ָ�ǰڳ�..
	FiniteStateMachine* fsm = new FiniteStateMachine();
	//�������� ���ϴ°� �� ĳ���͸��� fsm�� ���θ��� ��ӹ޾Ƽ� �������ϰ�
	//�װ� �־�����ϴ°ǰ�? protected�� �����ҷ��� �װ� �³�����. 
	AddComponent(fsm); //������ �߶�������.. 
	fsm->CreateState<PlayerIdle>("Idle");
	fsm->CreateState<PlayerAttack>("Attack");
	fsm->CreateState<PlayerHit>("Hit");
	fsm->CreateState<PlayerDie>("Die");
	fsm->CreateState<PlayerRun>("Run");
	fsm->CreateState<PlayerJump>("Jump");
	fsm->SetNextState("Idle"); 
	//�÷��̾��� fsm ������Ʈ�� �־��ְ�.. 
	renderOrder = 100; 
	m_Transform->m_RelativeScale = { 3,3 };
}

Character::~Character()
{

}

void Character::Update(float deltaTime) //������ aabb�� ���� ������� ó���ϸ����հ� �������ϰ�.. 
{
	__super::Update(deltaTime);//�θ��� ������Ʈ�� �ѹ� ȣ���ؾ߰���?
}

void Character::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);
}
