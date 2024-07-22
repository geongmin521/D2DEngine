#include "pch.h"
#include "Collider.h"
#include "CollisionManager.h"

Collider::Collider()
{
	CollisionManager::GetInstance()->pushCollider(this);

}

void Collider::ClearAndBackupCollideState()
{
}

void Collider::ProcessOverlap()
{
}

void Collider::ProcessBlock(Collider* pOtherComponent)
{
	notify->OnBlock(pOtherComponent);

}
