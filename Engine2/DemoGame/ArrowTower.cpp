#include "../D2DEngine/pch.h"
#include "../D2DEngine/BoxCollider.h"
#include "../D2DEngine/Bitmap.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/D2DRenderer.h"
#include "../D2DEngine/AABB.h"
#include "../D2DEngine/Music.h"
#include "ArrowTower.h"

ArrowTower::ArrowTower()
{
	SetBoundBox(0, 0, 100, 100);
	AddComponent(new Bitmap(L"..\\Data\\Image\\castle.png"));

	//�̹����� ��������.. �ڵ����� ȸ���� �߽���ǥ�� �����ϱ�.. 
	transform->SetImageCenter({
		GetComponent<Bitmap>()->bitmap->GetSize().width*0.2f / 2 ,GetComponent<Bitmap>()->bitmap->GetSize().height * 0.2f / 2 });
	AddComponent(new BoxCollider(boundBox ,CollisionType::Block, this, CollisionLayer::Tower));
	//�ڽ��� ������ �پ��� ���� ��ġ�� ȸ���ϴµ� �ֱ׷���>? 

	renderOrder = 100;
	transform->relativeScale = { 0.2f,0.2f };
}

ArrowTower::~ArrowTower()
{
}

void ArrowTower::Update(float deltaTime)
{
	__super::Update(deltaTime);
	Music::soundManager->GetInstance()->PlayMusic();
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
