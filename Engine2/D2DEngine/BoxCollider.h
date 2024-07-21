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
	//�浹������ ��ģ���� ���������?  �ݶ��̴����� �ý����� �̷��� �޶󵵵Ǵ°ǰ�?
	virtual bool IsCollide(Collider* pOtherComponent) override;
	virtual bool IsCollide(AABB* aabb) override;
	virtual	void ProcessBlock(Collider* pOtherComponent) override;
	
};

