#include "../D2DEngine/pch.h"
#include "../D2DEngine/MathHelper.h"
#include "../D2DEngine/Movement.h"
#include "../D2DEngine/Bitmap.h"
#include "../D2DEngine/BoxCollider.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/D2DRenderer.h"
#include "SpiderWeb.h"

SpiderWeb::SpiderWeb()
{
	isActive = false;//자식오브젝트가 될거란 말이지? 부모설정을 부모에서 해야하나 자식에서 해야하나? 
	AddComponent(new Movement(this->m_Transform,false));
	AddComponent(new BoxCollider(this->m_BoundBox,CollisionType::Block,this, CollisionLayer::Web));
	AddComponent(new Bitmap(L"..\\Data\\web.png"));
	Speed = 300;
	MaxDistance = 1000; //최대길이
}

//이친구가 부모가 되는게 맞지않나? 나중에 애를 중심으로 회전해야하는데..,. 
//그럼 입력에 의한 이동을 부모로 해야하나? 

SpiderWeb::~SpiderWeb()
{
}

void SpiderWeb::Fire(MathHelper::Vector2F dir)
{
	m_Transform->Update(1); //비활성화 되어있을때 트랜스폼 없데이트가 안돌아서 .. 
	//오브젝트이 비활성화도 있고 컴포넌트의 비활성화도 있고흠.. 비활성화 되어있어도 컴포넌트 업데이트는 돌리는게맞나? 
	dir = dir.Normalize(); //원래해서 보내는게 맞지만 혹시 모르니 여기서 한번더 처리하기로
	Direction = dir;
	StartPoint = this->m_Transform->GetWorldLocation();
	GetComponent<Movement>()->SetVelocity(Direction * Speed);
}

//닿으면 플레이어도 거리가 일정량 이하가 될때까지 줄어들게하자 그래야 궤도 운동을하지

void SpiderWeb::Update(float deltaTime)//이것도 생각해보니까 fsm인가? 
{
	__super::Update(deltaTime); //공유전이를 각상태에서 부모를 호출하는게 아니라..
	//부모를 먼저 한번 돌리고 나머지 상태를 돌려야겠는데? 오케이확인. 
	//상대좌표가 이상한데? 
	float distance = (StartPoint - this->m_Transform->GetWorldLocation()).Length();
	if (distance < this->MaxDistance) //현재 위치에서 시작 위치를 뺀 벡터의 길이가 지금까지 날아간 거리
	{
		
	}		
	else
	{
		GetComponent<Movement>()->SetVelocity(m_Transform->m_RelativeLocation * -1);//본인 위치로 돌아가기
		if (m_Transform->m_RelativeLocation.Length() < 1)
		{
			isActive = false; //비활성화하기
		}
		//마우스누르면 플레이어에서 마우스포즈까지 방향으로 일정거리만큼 나가고(던질수있는 상태인지 검사)
		//벽에 부딪히면 부착성공 아니면 상대좌표가 0,0일때까지 돌아오고
		//부착되면 살짝 떠오르고 부딪히기 전까지 궤도 운동가능 원점이 이게되는거고. 
		//이거랑 사진 외적까지만하면 완성일듯? 

		//왼쪽마우스클릭하면 
	}
}

void SpiderWeb::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget); //어차피 그리전에 렌더타겟의 셋 트랜스폼을 해놓으니까.. 
	//0,0에서 그려야하나? 
	//MathHelper
	pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());//아 트랜스폼 계산하기 머리아프다
	D2DRenderer::GetInstance()->DrawLine( player->GetWorldLocation(), m_Transform->GetWorldLocation());
	//선그리는거 있는데.. //좌표가 중앙이 아니라서 하.. 
}

void SpiderWeb::OnBlock(Collider* pOtherComponent)
{
	if (pOtherComponent->GetCollisionLayer() == CollisionLayer::Platform) //벽이면 거기 붙기
	{
		attach = true;
		GetComponent<Movement>()->SetVelocity({ 0,0 });
	}
		
	//플레이어한테 상태를 보내줘야하는데? 
	//아니야 ㅣ플레이어의 상태가 웹의 상태를 공유전이에서? 기다리다 
	//거리가 줄어들때 까지 가다가 스윙해주기. 
}

void SpiderWeb::OnBeginOverlap(Collider* pOtherComponent)
{
}

void SpiderWeb::OnEndOverlap(Collider* pOtherComponent)
{
}
