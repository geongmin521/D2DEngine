#pragma once
#include "Component.h"
//#include "AABB.h"

class Transform;
class AABB;
class RigidBody :
    public Component
{

public:
    //이친구는 트랜스폼에 접근해야만함.. 
	//그리고 충돌도 담당해야하니까 aabb도 들고있어야하고.. 
	RigidBody(Transform* transform, bool isGravity = true);
	virtual ~RigidBody();
	Transform* tr;
	AABB* aabb;
	bool isGravity;
	float GravityScale;
	virtual void Update(float deltaTime);
	virtual void Render(ID2D1RenderTarget* pRenderTarget, D2D1_MATRIX_3X2_F transform);
};

