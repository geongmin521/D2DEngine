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
	AddComponent(new BoxCollider(m_BoundBox, CollisionType::Block,this)); //m_BoundBox 이것도 애니메이션에서 바꿔주는거아니였나

	AddComponent(new Movement(m_Transform ,true)); //이제 방향만 지정해주면되겠네..
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
	isBlock[0] = false; //초기화해주기
	isBlock[1] = false;
	
	float MoveX = 0;
	float MoveY = 0;
	if (inputSystem->isKey(VK_RIGHT)) 
	{
		MoveX = 1 * speed;

	}
	if (inputSystem->isKey(VK_LEFT)) //상태에 재진입을안하는구나
	{
		MoveX = -1 * speed;	//y축이동이랑 x축 이동 속도가 다를수도있겠구나.. 
	}
	if (inputSystem->isKeyDown(VK_SPACE))
	{
		isground = false;
		MoveY = -1 * Jumpspeed;//땅에 닿았다는거는 어떻게 알지? 
	}
	GetComponent<Movement>()->AddVelocity({ MoveX, MoveY }); //진짜 개망했네 내일 하자.. 

	__super::Update(deltaTime);//부모의 업데이트를 한번 호출해야겠지? 마지막에 호출한다면?
}

void Character::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);
	D2DRenderer::GetInstance()->DrawTextFunc(std::to_wstring(GetComponent<Movement>()->GetVelocity().x) , 0, 0);
	D2DRenderer::GetInstance()->DrawTextFunc(std::to_wstring(isBlock[0]) , 0, 100);
	D2DRenderer::GetInstance()->DrawTextFunc(std::to_wstring(isBlock[1]) , 0, 200);
	D2DRenderer::GetInstance()->DrawAABB(*m_BoundBox); //얘 박스가 왜 저기있을까? 아 박스도 화면중앙에 올수있게 해줘야하는구나.. 
}

void Character::OnBlock(Collider* pOtherComponent)  //생각해보니 본인 콜라이더가 여러개일수있으니 본인 콜라이더가 필요하겠구나.. 
{
	AABB prevXBox = *m_BoundBox, prevYBox = *m_BoundBox; //이게 아마 현재 충돌한 위치일텐데.. 
	prevXBox.m_Center.x = GetComponent<Movement>()->GetPrevPos().x;//이동으로 가기전위치 
	prevYBox.m_Center.y = GetComponent<Movement>()->GetPrevPos().y; //이전위치가 아니네.. 
	isBlock[0] = !pOtherComponent->IsCollide(&prevXBox); //이전위치로 갔는데도 충돌했다면 충돌에 관여하지않음.. 즉 이동할 필요가없음 //그러니까 현재와 현재로 둘다 같은결과니까 다른결과가 나올리가 없지. 
	isBlock[1] = !pOtherComponent->IsCollide(&prevYBox); //그렇네 이전위치로 갔는데 왜 충돌함? 
	GetComponent<Movement>()->PrevPosition(isBlock[0], isBlock[1]); //다시 충돌해도 충돌했다면 그축은 관여하지않는다는거고
	
	if (isBlock[1] == true)
	{
		isground = true;
	}
	//충돌하지않는다면 그축으로인해 충돌이 일어난거임
}

void Character::OnBeginOverlap(Collider* pOtherComponent)
{
}

void Character::OnEndOverlap(Collider* pOtherComponent)
{
}
