#pragma once
#include "Collider.h"

class AABB;
class BoxCollider :public Collider
{
public:
	AABB* aabb;
	virtual bool IsCollide(Collider* pOtherComponent) override;
};

