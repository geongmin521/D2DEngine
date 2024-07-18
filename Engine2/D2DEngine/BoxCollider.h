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
	//�浹������ ��ģ���� ���������?  �ݶ��̴����� �ý����� �̷��� �޶󵵵Ǵ°ǰ�?
	virtual bool IsCollide(Collider* pOtherComponent) override;
	virtual	void ProcessBlock(Collider* pOtherComponent) override;
	
};

