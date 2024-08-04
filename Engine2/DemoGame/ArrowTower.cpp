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
	//이걸 간략하게 표현할 방법 생각해보기.. 특히 자동으로 될수있게.. 이미지가 가져와진 시점이면서 렌더 컴포넌트가 주인을 알게되는시점.. 
	transform->SetImageCenter({ GetComponent<Bitmap>()->bitmap->GetSize().width*0.2f / 2 ,GetComponent<Bitmap>()->bitmap->GetSize().height * 0.2f / 2 }); //스케일도 적용받아야함.. 
	//콜라이더 좌표도 엄청이상하네.. 이건 좀더 생각해보고 피곤하니까 자자..
	//근데 이래도 중심으로 안도네?
	AddComponent(new BoxCollider(boundBox ,CollisionType::Block, this, CollisionLayer::Tower));
	//boundBox이거의 센터는 업데이트를 받아올텐데.. //렌더순서가 뒤라그런가? 
	renderOrder = 100;
	transform->relativeScale = { 0.2f,0.2f }; //좌표가 0,0이면 화면 맨 왼쪽 위에 그리는거지? 

	//transform->m_RelativeLocation = { WinHalfSizeX, WinHalfSizeY };
}

ArrowTower::~ArrowTower()
{
}

void ArrowTower::Update(float deltaTime)
{
	__super::Update(deltaTime);

	//테스트용으로 회전걸어놓고 중앙을 기준으로 회전하도록만들기
	transform->AddRelativeRotation(1);
}

void ArrowTower::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);
	//GetComponent<BoxCollider>()->aabb->Center = { 300,300 };
	//D2DRenderer::GetInstance()->DrawAABB(*GetComponent<BoxCollider>()->aabb); //위치가 이상한듯? 흠 잘그리는데.. 뭐한 띄워봐야하니까 원일일수있는거 다 검사해보자
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
