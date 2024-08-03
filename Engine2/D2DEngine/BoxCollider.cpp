#include "pch.h"
#include "BoxCollider.h"
#include "GameObject.h"
#include "Movement.h"
#include "Transform.h"
#include "AABB.h"


BoxCollider::BoxCollider(AABB* aabb, CollisionType type, IColliderNotify* notify, CollisionLayer layer = CollisionLayer::Default)
    : aabb(aabb)
{
    collisionType = type;
    this->layer = layer;
    this->notify = notify;
}

BoxCollider::~BoxCollider()
{

}

bool BoxCollider::IsCollide(Collider* otherComponent)
{
    //�浹�ߴ����˻�
    return  aabb->CheckIntersect(*((BoxCollider*)otherComponent)->aabb);
    //�ϴ� �ڽ��ݶ��̴� �ۿ� �����ϱ� 
}

bool BoxCollider::IsCollide(AABB* aabb)
{
    return this->aabb->CheckIntersect(*aabb);;
}

void BoxCollider::ProcessBlock(Collider* otherComponent)
{
    __super::ProcessBlock(otherComponent);
}
