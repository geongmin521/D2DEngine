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
	isActive = false;//�ڽĿ�����Ʈ�� �ɰŶ� ������? �θ����� �θ𿡼� �ؾ��ϳ� �ڽĿ��� �ؾ��ϳ�? 
	AddComponent(new Movement(this->m_Transform,false));
	AddComponent(new BoxCollider(this->m_BoundBox,CollisionType::Block,this, CollisionLayer::Web));
	AddComponent(new Bitmap(L"..\\Data\\web.png"));
	Speed = 300;
	MaxDistance = 1000; //�ִ����
}

//��ģ���� �θ� �Ǵ°� �����ʳ�? ���߿� �ָ� �߽����� ȸ���ؾ��ϴµ�..,. 
//�׷� �Է¿� ���� �̵��� �θ�� �ؾ��ϳ�? 

SpiderWeb::~SpiderWeb()
{
}

void SpiderWeb::Fire(MathHelper::Vector2F dir)
{
	m_Transform->Update(1); //��Ȱ��ȭ �Ǿ������� Ʈ������ ������Ʈ�� �ȵ��Ƽ� .. 
	//������Ʈ�� ��Ȱ��ȭ�� �ְ� ������Ʈ�� ��Ȱ��ȭ�� �ְ���.. ��Ȱ��ȭ �Ǿ��־ ������Ʈ ������Ʈ�� �����°Ը³�? 
	dir = dir.Normalize(); //�����ؼ� �����°� ������ Ȥ�� �𸣴� ���⼭ �ѹ��� ó���ϱ��
	Direction = dir;
	StartPoint = this->m_Transform->GetWorldLocation();
	GetComponent<Movement>()->SetVelocity(Direction * Speed);
}

//������ �÷��̾ �Ÿ��� ������ ���ϰ� �ɶ����� �پ������� �׷��� �˵� �������

void SpiderWeb::Update(float deltaTime)//�̰͵� �����غ��ϱ� fsm�ΰ�? 
{
	__super::Update(deltaTime); //�������̸� �����¿��� �θ� ȣ���ϴ°� �ƴ϶�..
	//�θ� ���� �ѹ� ������ ������ ���¸� �����߰ڴµ�? ������Ȯ��. 
	//�����ǥ�� �̻��ѵ�? 
	float distance = (StartPoint - this->m_Transform->GetWorldLocation()).Length();
	if (distance < this->MaxDistance) //���� ��ġ���� ���� ��ġ�� �� ������ ���̰� ���ݱ��� ���ư� �Ÿ�
	{
		
	}		
	else
	{
		GetComponent<Movement>()->SetVelocity(m_Transform->m_RelativeLocation * -1);//���� ��ġ�� ���ư���
		if (m_Transform->m_RelativeLocation.Length() < 1)
		{
			isActive = false; //��Ȱ��ȭ�ϱ�
		}
		//���콺������ �÷��̾�� ���콺������� �������� �����Ÿ���ŭ ������(�������ִ� �������� �˻�)
		//���� �ε����� �������� �ƴϸ� �����ǥ�� 0,0�϶����� ���ƿ���
		//�����Ǹ� ��¦ �������� �ε����� ������ �˵� ����� ������ �̰ԵǴ°Ű�. 
		//�̰Ŷ� ���� �����������ϸ� �ϼ��ϵ�? 

		//���ʸ��콺Ŭ���ϸ� 
	}
}

void SpiderWeb::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget); //������ �׸����� ����Ÿ���� �� Ʈ�������� �س����ϱ�.. 
	//0,0���� �׷����ϳ�? 
	//MathHelper
	pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());//�� Ʈ������ ����ϱ� �Ӹ�������
	D2DRenderer::GetInstance()->DrawLine( player->GetWorldLocation(), m_Transform->GetWorldLocation());
	//���׸��°� �ִµ�.. //��ǥ�� �߾��� �ƴ϶� ��.. 
}

void SpiderWeb::OnBlock(Collider* pOtherComponent)
{
	if (pOtherComponent->GetCollisionLayer() == CollisionLayer::Platform) //���̸� �ű� �ٱ�
	{
		attach = true;
		GetComponent<Movement>()->SetVelocity({ 0,0 });
	}
		
	//�÷��̾����� ���¸� ��������ϴµ�? 
	//�ƴϾ� ���÷��̾��� ���°� ���� ���¸� �������̿���? ��ٸ��� 
	//�Ÿ��� �پ�鶧 ���� ���ٰ� �������ֱ�. 
}

void SpiderWeb::OnBeginOverlap(Collider* pOtherComponent)
{
}

void SpiderWeb::OnEndOverlap(Collider* pOtherComponent)
{
}
