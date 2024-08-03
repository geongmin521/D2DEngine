#pragma once
#include "Collider.h"
#include "Component.h"
class AABB;
class IColliderNotify;
class BoxCollider :public Collider, public Component
{
public:
	BoxCollider(AABB* aabb, CollisionType type, IColliderNotify* notify, CollisionLayer layer);
	~BoxCollider();
	AABB* aabb;

	virtual bool IsCollide(Collider* otherComponent) override;
	virtual bool IsCollide(AABB* aabb) override;
	virtual	void ProcessBlock(Collider* otherComponent) override;
	
};

