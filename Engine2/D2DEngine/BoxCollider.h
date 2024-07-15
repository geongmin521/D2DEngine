#pragma once
#include "Collider.h"

class AABB;
class BoxCollider : public Collider , public IColliderNotify
{
public:
	AABB* aabb;
	virtual void OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent) override;
	virtual void OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;
	virtual void OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;
	virtual bool IsCollide(Collider* pOtherComponent) override;
};

