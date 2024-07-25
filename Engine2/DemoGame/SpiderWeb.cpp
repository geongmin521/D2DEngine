#include "../D2DEngine/pch.h"
#include "../D2DEngine/MathHelper.h"
#include "../D2DEngine/Movement.h"
#include "../D2DEngine/Bitmap.h"
#include "../D2DEngine/BoxCollider.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/D2DRenderer.h" //이 헤더들도 어떻게 하고싶은데.. 
#include "Character.h"//이 헤더들도 어떻게 하고싶은데.. 
#include "SpiderWeb.h"

SpiderWeb::SpiderWeb()
{
	isActive = false;//자식오브젝트가 될거란 말이지? 부모설정을 부모에서 해야하나 자식에서 해야하나? 
	AddComponent(new Movement(this->m_Transform));
	AddComponent(new BoxCollider(this->m_BoundBox,CollisionType::Block,this, CollisionLayer::Web));
	AddComponent(new Bitmap(L"..\\Data\\web.png"));
	Speed = 500;
	MaxDistance = 1000; //최대길이
}

//이친구가 부모가 되는게 맞지않나? 나중에 애를 중심으로 회전해야하는데..,. 
//그럼 입력에 의한 이동을 부모로 해야하나? 

SpiderWeb::~SpiderWeb()
{
}

void SpiderWeb::Fire(MathHelper::Vector2F dir)
{
	m_Transform->Update(1);
	dir = dir.Normalize();
	Direction = dir;
	StartPoint = this->m_Transform->GetWorldLocation();
	GetComponent<Movement>()->SetVelocity(Direction * Speed);
}

void SpiderWeb::Update(float deltaTime)
{
	__super::Update(deltaTime); 
	float distance = (StartPoint - this->m_Transform->GetWorldLocation()).Length();
	if (distance < this->MaxDistance)  //스파이더 웹 업데이트 다시보기
	{
		
	}		
	else
	{
		GetComponent<Movement>()->SetVelocity(m_Transform->m_RelativeLocation * -1);
		if (m_Transform->m_RelativeLocation.Length() < 1)
		{
			isActive = false; 
		}
	}
}

void SpiderWeb::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget); 
	pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	D2DRenderer::GetInstance()->DrawLine( player->GetWorldLocation(), m_Transform->GetWorldLocation());

}

void SpiderWeb::OnBlock(Collider* pOtherComponent)
{
	if (pOtherComponent->GetCollisionLayer() == CollisionLayer::Platform)
	{
		player->ishanging = true;
		GetComponent<Movement>()->PrevPosition(false, true);
		GetComponent<Movement>()->SetVelocity({ 0,0 });
	}
}

void SpiderWeb::OnBeginOverlap(Collider* pOtherComponent)
{
}

void SpiderWeb::OnEndOverlap(Collider* pOtherComponent)
{
}
