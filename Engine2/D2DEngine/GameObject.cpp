#include "pch.h"
#include "GameObject.h"
//#include "Component.h"
#include "AABB.h"
#include "D2DRenderer.h"
#include "Transform.h"

GameObject::GameObject()
{
	m_Transform = new Transform(); //��� ���ӿ�����Ʈ�� Ʈ�������� ����ִ�.
	AddComponent(m_Transform);
	m_BoundBox = new AABB();
}

GameObject::~GameObject()
{
	for (auto& pComponent : m_OwnedComponents)
	{
		delete pComponent;
	}
	m_OwnedComponents.clear();
}

void GameObject::Update(float deltaTime)
{
	for (auto& pComponent : m_OwnedComponents)
	{
		pComponent->Update(deltaTime);
	}
	if (m_Transform)
		m_BoundBox->m_Center = m_Transform->GetWorldLocation();
}


void GameObject::Render(ID2D1HwndRenderTarget* pRenderTarget)//����������.. �����ΰ��� �� ��Ƴ��� �ʿ䰡 ��������?
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