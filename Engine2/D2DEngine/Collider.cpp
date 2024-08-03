#include "pch.h"
#include "Collider.h"
#include "CollisionManager.h"

Collider::Collider()
{
	CollisionManager::GetInstance()->pushCollider(this);

}

Collider::~Collider()
{
	CollisionManager::GetInstance()->EraseCollider(this);
}

void Collider::ClearAndBackupCollideState()
{
}

void Collider::ProcessOverlap()
{
}

void Collider::ProcessBlock(Collider* otherComponent)
{
	notify->OnBlock(otherComponent);

}
