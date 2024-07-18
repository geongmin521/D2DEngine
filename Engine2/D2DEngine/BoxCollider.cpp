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
    //충돌했는지검사
    return  aabb->CheckIntersect(*((BoxCollider*)pOtherComponent)->aabb);
    //일단 박스콜라이더 밖에 없으니까 
}

void BoxCollider::ProcessBlock(Collider* pOtherComponent)
{
    //인포를 그냥 가지고있고 지우는게 낫지않나? 
    aabb->CheckCollisionInfo(*((BoxCollider*)pOtherComponent)->aabb,*info);
    m_pOwner->GetComponent<Movement>()->isBlock[(int)info->dir] = false;//나중에는 메세지시스템을 만들어서 컴포넌트끼리의 참조를 없애도록하자.. 
    //방향을 설정? 
    if(info->dir == CollisionDir::Top)
        m_pOwner->GetComponent<Transform>()->m_RelativeLocation.y += info->depth;
    if (info->dir == CollisionDir::Bottom)                                
        m_pOwner->GetComponent<Transform>()->m_RelativeLocation.y -= info->depth;
    if (info->dir == CollisionDir::Right)                                 
        m_pOwner->GetComponent<Transform>()->m_RelativeLocation.x -= info->depth;
    if (info->dir == CollisionDir::Left)                                  
        m_pOwner->GetComponent<Transform>()->m_RelativeLocation.x += info->depth;
}
