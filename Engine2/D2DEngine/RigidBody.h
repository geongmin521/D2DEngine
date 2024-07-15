#pragma once
#include "Component.h"
//#include "AABB.h"

class Transform;
class AABB;
class RigidBody :
    public Component
{

public:
    //��ģ���� Ʈ�������� �����ؾ߸���.. 
	//�׸��� �浹�� ����ؾ��ϴϱ� aabb�� ����־���ϰ�.. 
	RigidBody(Transform* transform, bool isGravity = true);
	virtual ~RigidBody();
	Transform* tr;
	AABB* aabb;
	bool isGravity;
	float GravityScale;
	virtual void Update(float deltaTime);
	virtual void Render(ID2D1RenderTarget* pRenderTarget, D2D1_MATRIX_3X2_F transform);
};

