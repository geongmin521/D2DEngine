#include "pch.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "GameObject.h"
#include "Movement.h"
#include "Transform.h"
#include "AABB.h"
#include "D2DRenderer.h"


BoxCollider::BoxCollider(AABB* aabb, CollisionType type, IColliderNotify* notify, CollisionLayer layer = CollisionLayer::Default)
    : aabb(aabb)
{
    colliderType = ColliderType::Box;
    collisionType = type;
    this->layer = layer;
    this->notify = notify;
}

BoxCollider::~BoxCollider()
{

}

bool BoxCollider::IsCollide(Collider* otherComponent) 
{
    if (otherComponent->GetColliderType() == ColliderType::Box) //��밡 �ڽ��϶�
    {
        return  aabb->CheckIntersect(*((BoxCollider*)otherComponent)->aabb);
    }
    else if (otherComponent->GetColliderType() == ColliderType::Circle) //��밡 ���϶�
    {
        return  aabb->CheckIntersect(*((CircleCollider*)otherComponent)->aabb);
    }
}

void BoxCollider::ProcessBlock(Collider* ownedComponent, Collider* otherComponent)
{
    __super::ProcessBlock(ownedComponent, otherComponent);
}

void BoxCollider::Update(float deltaTime)
{
    if (owner->transform)
        aabb->Center = owner->transform->GetWorldLocation(); //�̺κ��� �� �ݶ��̴��� �����Ѵ�
    //�޾ƿ��°� ������ǥ�ε�.. 
}

//�׸��� ��ġ�� �����϶��� ��������

void BoxCollider::Render(ID2D1RenderTarget* pRenderTarget)
{
#ifdef _DEBUG
    D2DRenderer::GetInstance()->DrawAABB(*aabb);
#endif
}
