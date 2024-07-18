#pragma once
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/IColliderNotify.h" 


class Character :
    public GameObject, public IColliderNotify
{
private:
	float speed;
public:
	Character();
	virtual ~Character();	
	virtual void Update(float deltaTime);
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);

	virtual void OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent) override;
	virtual void OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;
	virtual void OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;
};

