#pragma once
#include "Collider.h"
#include "Component.h"
class AABB;
class IColliderNotify;
class BoxCollider :public Collider, public Component
{
public:
	BoxCollider(AABB* aabb, CollisionType type, IColliderNotify* notify);
	~BoxCollider();
	AABB* aabb;
	//충돌정보를 이친구가 들고있을까?  콜라이더마다 시스템이 이렇게 달라도되는건가?
	virtual bool IsCollide(Collider* pOtherComponent) override;
	virtual bool IsCollide(AABB* aabb) override;
	virtual	void ProcessBlock(Collider* pOtherComponent) override;
	
};

