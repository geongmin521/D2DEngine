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
	speed = 100;
	Jumpspeed = 1000;
	AddComponent(new Animation(L"..\\Data\\spider.png", L"SpiderMan"));
	AddComponent(new RigidBody(m_Transform)); 
	AddComponent(new BoxCollider(m_BoundBox, CollisionType::Block,this)); //m_BoundBox �̰͵� �ִϸ��̼ǿ��� �ٲ��ִ°žƴϿ���

	AddComponent(new Movement(m_Transform ,true)); //���� ���⸸ �������ָ�ǰڳ�..
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
	m_Transform->m_RelativeLocation = { WinHalfSizeX, WinHalfSizeY };//ī�޶󶧸� ���� ���� ����� ������ ����� �ٸ��� ������... 
}

Character::~Character()
{

}

void Character::Update(float deltaTime) //������ aabb�� ���� ������� ó���ϸ����հ� �������ϰ�.. 
{
	isBlock[0] = false; //�ʱ�ȭ���ֱ�
	isBlock[1] = false;
	
	float MoveX = 0;
	float MoveY = 0;
	if (inputSystem->isKey(VK_RIGHT)) 
	{
		MoveX = 1 * speed;

	}
	if (inputSystem->isKey(VK_LEFT)) //���¿� �����������ϴ±���
	{
		MoveX = -1 * speed;	//y���̵��̶� x�� �̵� �ӵ��� �ٸ������ְڱ���.. 
	}
	if (inputSystem->isKeyDown(VK_SPACE))
	{
		isground = false;
		MoveY = -1 * Jumpspeed;//���� ��Ҵٴ°Ŵ� ��� ����? 
	}
	GetComponent<Movement>()->AddVelocity({ MoveX, MoveY }); //��¥ �����߳� ���� ����.. 

	__super::Update(deltaTime);//�θ��� ������Ʈ�� �ѹ� ȣ���ؾ߰���? �������� ȣ���Ѵٸ�?
}

void Character::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);
	D2DRenderer::GetInstance()->DrawTextFunc(std::to_wstring(GetComponent<Movement>()->GetVelocity().x) , 0, 0);
	D2DRenderer::GetInstance()->DrawTextFunc(std::to_wstring(isBlock[0]) , 0, 100);
	D2DRenderer::GetInstance()->DrawTextFunc(std::to_wstring(isBlock[1]) , 0, 200);
	D2DRenderer::GetInstance()->DrawAABB(*m_BoundBox); //�� �ڽ��� �� ����������? �� �ڽ��� ȭ���߾ӿ� �ü��ְ� ������ϴ±���.. 
}

void Character::OnBlock(Collider* pOtherComponent)  //�����غ��� ���� �ݶ��̴��� �������ϼ������� ���� �ݶ��̴��� �ʿ��ϰڱ���.. 
{
	AABB prevXBox = *m_BoundBox, prevYBox = *m_BoundBox; //�̰� �Ƹ� ���� �浹�� ��ġ���ٵ�.. 
	prevXBox.m_Center.x = GetComponent<Movement>()->GetPrevPos().x;//�̵����� ��������ġ 
	prevYBox.m_Center.y = GetComponent<Movement>()->GetPrevPos().y; //������ġ�� �ƴϳ�.. 
	isBlock[0] = !pOtherComponent->IsCollide(&prevXBox); //������ġ�� ���µ��� �浹�ߴٸ� �浹�� ������������.. �� �̵��� �ʿ䰡���� //�׷��ϱ� ����� ����� �Ѵ� ��������ϱ� �ٸ������ ���ø��� ����. 
	isBlock[1] = !pOtherComponent->IsCollide(&prevYBox); //�׷��� ������ġ�� ���µ� �� �浹��? 
	GetComponent<Movement>()->PrevPosition(isBlock[0], isBlock[1]); //�ٽ� �浹�ص� �浹�ߴٸ� ������ ���������ʴ´ٴ°Ű�
	
	if (isBlock[1] == true)
	{
		isground = true;
	}
	//�浹�����ʴ´ٸ� ������������ �浹�� �Ͼ����
}

void Character::OnBeginOverlap(Collider* pOtherComponent)
{
}

void Character::OnEndOverlap(Collider* pOtherComponent)
{
}
