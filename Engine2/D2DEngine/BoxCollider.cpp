#include "pch.h"
#include "BoxCollider.h"
#include "GameObject.h"
#include "Movement.h"
#include "Transform.h"
#include "AABB.h"

BoxCollider::BoxCollider(AABB* aabb) : aabb(aabb)
{
    info = new CollisionInfo();
}

BoxCollider::~BoxCollider()
{
    delete info;
}

bool BoxCollider::IsCollide(Collider* pOtherComponent)
{
    //�浹�ߴ����˻�
    return  aabb->CheckIntersect(*((BoxCollider*)pOtherComponent)->aabb);
    //�ϴ� �ڽ��ݶ��̴� �ۿ� �����ϱ� 
}

void BoxCollider::ProcessBlock(Collider* pOtherComponent)
{
    //������ �׳� �������ְ� ����°� �����ʳ�? 
    aabb->CheckCollisionInfo(*((BoxCollider*)pOtherComponent)->aabb,*info);
    m_pOwner->GetComponent<Movement>()->isBlock[(int)info->dir] = false;//���߿��� �޼����ý����� ���� ������Ʈ������ ������ ���ֵ�������.. 
    //������ ����? 
    if(info->dir == CollisionDir::Top)
        m_pOwner->GetComponent<Transform>()->m_RelativeLocation.y += info->depth;
    if (info->dir == CollisionDir::Bottom)                                
        m_pOwner->GetComponent<Transform>()->m_RelativeLocation.y -= info->depth;
    if (info->dir == CollisionDir::Right)                                 
        m_pOwner->GetComponent<Transform>()->m_RelativeLocation.x -= info->depth;
    if (info->dir == CollisionDir::Left)                                  
        m_pOwner->GetComponent<Transform>()->m_RelativeLocation.x += info->depth;
}
