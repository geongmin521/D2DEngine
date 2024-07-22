#pragma once
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/MathHelper.h"
#include "../D2DEngine/IColliderNotify.h"

class Missile :public GameObject ,public IColliderNotify
{
public:
	float distance;
	float Timer;
	float speed;
	Transform* target;
	MathHelper::Vector2F dir;

	Missile();
	~Missile();
	virtual void Update(float deltaTime) override;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget) override;
	virtual void OnBlock(Collider* pOtherComponent) override;
	virtual void OnBeginOverlap(Collider* pOtherComponent) override;
	virtual void OnEndOverlap(Collider* pOtherComponent) override;
};

