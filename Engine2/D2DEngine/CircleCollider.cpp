#include "pch.h"
#include "CircleCollider.h"
#include "BoxCollider.h"
#include "AABB.h"
#include "Circle.h"
#include "D2DRenderer.h"
#include "GameObject.h"
#include "Transform.h"

CircleCollider::CircleCollider(AABB* aabb, Circle* circle, CollisionType type, IColliderNotify* notify, CollisionLayer layer) : aabb(aabb), circle(circle)
{
	colliderType = ColliderType::Circle;
	collisionType = type; //�Ʒ� �κ��� ��ġ�ϱ� �θ�����ڿ��� ó���ص� �ɵ�? 
	this->layer = layer;
	this->notify = notify;
}

CircleCollider::~CircleCollider()
{
}

bool CircleCollider::IsCollide(Collider* otherComponent)
{
	//��밡 ��Ŭ�϶���, �ڽ��϶�  �� �ΰ�� ���� //�ڽ����� �� ��Ŭ���� ��.. 
	if (otherComponent->GetColliderType() == ColliderType::Box)
	{
		return  aabb->CheckIntersect(*((BoxCollider*)otherComponent)->aabb);
	}
	else
	{
		return  circle->CheckIntersect(*((CircleCollider*)otherComponent)->circle);
	}
}

void CircleCollider::Update(float deltaTime)
{
	if (owner->transform)
		aabb->Center = owner->transform->GetWorldLocation(); //�̺κ��� �� �ݶ��̴��� �����Ѵ�
}

void CircleCollider::Render(ID2D1RenderTarget* pRenderTarget)
{
#ifdef _DEBUG
	D2DRenderer::GetInstance()->DrawAABB(*aabb);
	D2DRenderer::GetInstance()->DrawCircle(*circle);
#endif
}

void CircleCollider::ProcessBlock(Collider* ownedComponent, Collider* otherComponent)
{
	__super::ProcessBlock(ownedComponent, otherComponent);
}
