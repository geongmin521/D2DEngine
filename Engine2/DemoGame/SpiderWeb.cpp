#include "../D2DEngine/pch.h"
#include "../D2DEngine/MathHelper.h"
#include "../D2DEngine/Movement.h"
#include "../D2DEngine/Bitmap.h"
#include "../D2DEngine/BoxCollider.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/D2DRenderer.h" //�� ����鵵 ��� �ϰ������.. 
#include "Character.h"//�� ����鵵 ��� �ϰ������.. 
#include "SpiderWeb.h"

SpiderWeb::SpiderWeb()
{
	isActive = false;//�ڽĿ�����Ʈ�� �ɰŶ� ������? �θ����� �θ𿡼� �ؾ��ϳ� �ڽĿ��� �ؾ��ϳ�? 
	AddComponent(new Movement(this->m_Transform));
	AddComponent(new BoxCollider(this->m_BoundBox,CollisionType::Block,this, CollisionLayer::Web));
	AddComponent(new Bitmap(L"..\\Data\\web.png"));
	Speed = 500;
	MaxDistance = 1000; //�ִ����
}

//��ģ���� �θ� �Ǵ°� �����ʳ�? ���߿� �ָ� �߽����� ȸ���ؾ��ϴµ�..,. 
//�׷� �Է¿� ���� �̵��� �θ�� �ؾ��ϳ�? 

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
	if (distance < this->MaxDistance)  //�����̴� �� ������Ʈ �ٽú���
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
