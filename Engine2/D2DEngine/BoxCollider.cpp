#include "pch.h"
#include "BoxCollider.h"
#include "GameObject.h"
#include "Movement.h"
#include "Transform.h"
//#include "IColliderNotify.h"
#include "AABB.h"


BoxCollider::BoxCollider(AABB* aabb, CollisionType type, IColliderNotify* notify, CollisionLayer layer = CollisionLayer::Default)
    : aabb(aabb)
{
    m_CollisionType = type;
    this->layer = layer;
    this->notify = notify;
}

BoxCollider::~BoxCollider()
{

}

bool BoxCollider::IsCollide(Collider* pOtherComponent)
{
    //충돌했는지검사
    return  aabb->CheckIntersect(*((BoxCollider*)pOtherComponent)->aabb);
    //일단 박스콜라이더 밖에 없으니까 
}

bool BoxCollider::IsCollide(AABB* aabb)
{
    return this->aabb->CheckIntersect(*aabb);;
}

void BoxCollider::ProcessBlock(Collider* pOtherComponent)
{
    __super::ProcessBlock(pOtherComponent);
}
