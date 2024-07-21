#include "pch.h"
#include "GameObject.h"
//#include "Component.h"
#include "AABB.h"
#include "D2DRenderer.h"
#include "Transform.h"

GameObject::GameObject()
{
	m_Transform = new Transform(); //모든 게임오브젝트는 트랜스폼을 들고있다.
	AddComponent(m_Transform);
	m_BoundBox = new AABB();
}

GameObject::~GameObject() //컴포넌트끼리의 비교우위를 줄수있을까? 
{
	for (auto& pComponent : m_OwnedComponents)
	{
		delete pComponent;
	}
	m_OwnedComponents.clear();
}

void GameObject::Update(float deltaTime) //컴포넌트를 넣을때 우선순위큐를 적용해서 넣으면 넣는 순간에 상관없이 정렬할수있지않을까? 
{
	for (auto& pComponent : m_OwnedComponents)//컴포넌트들의 업데이트 순서를 조정하는방법은 넣는 순서밖에 없나 이것도 좀 그런거같고.. 무브먼트를 먼저하고 
	{
		pComponent->Update(deltaTime);
	}
	if (m_Transform)
		m_BoundBox->m_Center = m_Transform->GetWorldLocation(); //트랜스폼이 월드 좌표를구하고 무브먼트가 상대좌표를 변경해봤자 월드는 안바뀌니까 박스는 이전좌표가 맞아. 
}


void GameObject::Render(ID2D1HwndRenderTarget* pRenderTarget)//렌더가능한.. 무엇인가를 또 모아놓을 필요가 있을려나?
{
	for (auto& pComponent : m_OwnedComponents) 
	{	
		pComponent->Render(pRenderTarget);
	}
}


void GameObject::SetBoundBox(int x, int y,int weight, int height)
{  
	if (m_BoundBox == nullptr)
		m_BoundBox = new AABB();
	m_BoundBox->SetExtent(weight / 2, height / 2);
	m_BoundBox->SetCenter(x,y);
}

void GameObject::AddComponent(Component* pComponent)
{
	pComponent->SetOwner(this);
	m_OwnedComponents.push_back(pComponent);
}

D2D1_VECTOR_2F GameObject::GetWorldLocation()
{ 
	D2D1_VECTOR_2F temp{ 0,0 };
	if (m_Transform)
		temp = m_Transform->GetWorldLocation();

	return temp;
}
