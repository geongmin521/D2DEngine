#include "pch.h"
#include "BoxCollider.h"
#include "GameObject.h"
#include "Movement.h"
#include "Transform.h"
//#include "IColliderNotify.h"
#include "AABB.h"


BoxCollider::BoxCollider(AABB* aabb, CollisionType type, IColliderNotify* notify) : aabb(aabb)
{
    m_CollisionType = type;
    this->notify = notify;
}

BoxCollider::~BoxCollider()
{

}

bool BoxCollider::IsCollide(Collider* pOtherComponent)
{
    //�浹�ߴ����˻�
    return  aabb->CheckIntersect(*((BoxCollider*)pOtherComponent)->aabb);
    //�ϴ� �ڽ��ݶ��̴� �ۿ� �����ϱ� 
}

void BoxCollider::ProcessBlock(Collider* pOtherComponent)
{
    __super::ProcessBlock(pOtherComponent);
}
