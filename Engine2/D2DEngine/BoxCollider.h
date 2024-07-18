#pragma once
#include "Collider.h"

class AABB;
class BoxCollider :public Collider
{
public:
	BoxCollider(AABB* aabb);
	~BoxCollider();
	AABB* aabb;
	CollisionInfo* info;
	//충돌정보를 이친구가 들고있을까?  콜라이더마다 시스템이 이렇게 달라도되는건가?
	virtual bool IsCollide(Collider* pOtherComponent) override;
	virtual	void ProcessBlock(Collider* pOtherComponent) override;
	
};

