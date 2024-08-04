#include "../D2DEngine/pch.h"
#include "../D2DEngine/BoxCollider.h"
#include "../D2DEngine/Bitmap.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/D2DRenderer.h"
#include "../D2DEngine/AABB.h"
#include "ArrowTower.h"

ArrowTower::ArrowTower()
{
	SetBoundBox(0, 0, 100, 100);
	AddComponent(new Bitmap(L"..\\Data\\Image\\castle.png"));
	//�̰� �����ϰ� ǥ���� ��� �����غ���.. Ư�� �ڵ����� �ɼ��ְ�.. �̹����� �������� �����̸鼭 ���� ������Ʈ�� ������ �˰ԵǴ½���.. 
	transform->SetImageCenter({ GetComponent<Bitmap>()->bitmap->GetSize().width*0.2f / 2 ,GetComponent<Bitmap>()->bitmap->GetSize().height * 0.2f / 2 }); //�����ϵ� ����޾ƾ���.. 
	//�ݶ��̴� ��ǥ�� ��û�̻��ϳ�.. �̰� ���� �����غ��� �ǰ��ϴϱ� ����..
	//�ٵ� �̷��� �߽����� �ȵ���?
	AddComponent(new BoxCollider(boundBox ,CollisionType::Block, this, CollisionLayer::Tower));
	//boundBox�̰��� ���ʹ� ������Ʈ�� �޾ƿ��ٵ�.. //���������� �ڶ�׷���? 
	renderOrder = 100;
	transform->relativeScale = { 0.2f,0.2f }; //��ǥ�� 0,0�̸� ȭ�� �� ���� ���� �׸��°���? 

	//transform->m_RelativeLocation = { WinHalfSizeX, WinHalfSizeY };
}

ArrowTower::~ArrowTower()
{
}

void ArrowTower::Update(float deltaTime)
{
	__super::Update(deltaTime);

	//�׽�Ʈ������ ȸ���ɾ���� �߾��� �������� ȸ���ϵ��ϸ����
	transform->AddRelativeRotation(1);
}

void ArrowTower::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);
	//GetComponent<BoxCollider>()->aabb->Center = { 300,300 };
	//D2DRenderer::GetInstance()->DrawAABB(*GetComponent<BoxCollider>()->aabb); //��ġ�� �̻��ѵ�? �� �߱׸��µ�.. ���� ��������ϴϱ� �����ϼ��ִ°� �� �˻��غ���
}

void ArrowTower::OnBlock(Collider* ownedComponent, Collider* otherComponent)
{
}

void ArrowTower::OnBeginOverlap(Collider* ownedComponent, Collider* otherComponent)
{
}

void ArrowTower::OnStayOverlap(Collider* ownedComponent, Collider* otherComponent)
{
}

void ArrowTower::OnEndOverlap(Collider* ownedComponent, Collider* otherComponent)
{
}
