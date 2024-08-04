#pragma once
#include "Collider.h"
#include "Component.h"

class AABB;
class Circle;
class IColliderNotify;
class CircleCollider :
    public Collider , public Component
{
public:
	AABB* aabb; //�ڽ��ݶ��̴��� �浹�Ҷ��� �̰ɷ� ����ϱ�
	Circle* circle;

	CircleCollider(AABB* aabb, Circle* circle, CollisionType type, IColliderNotify* notify, CollisionLayer layer);
	~CircleCollider();
	virtual bool IsCollide(Collider* otherComponent) override;
	virtual void Render(ID2D1RenderTarget* pRenderTarget) override;
	virtual void Update(float deltaTime)override;
	virtual	void ProcessBlock(Collider* ownedComponent,Collider* otherComponent) override;
};

