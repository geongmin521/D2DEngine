#include "pch.h"
#include "BoxCollider.h"

void BoxCollider::OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent)
{
}

void BoxCollider::OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
}

void BoxCollider::OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
}

bool BoxCollider::IsCollide(Collider* pOtherComponent)
{
    return false;
}
