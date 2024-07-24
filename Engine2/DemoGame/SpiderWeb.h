#pragma once
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/IColliderNotify.h"

class SpiderWeb :public GameObject ,public IColliderNotify
{
private:
	MathHelper::Vector2F Direction;
	MathHelper::Vector2F StartPoint;
	
	float Speed;
	float MaxDistance;
	bool attach = false;
public:
	Transform* player;
	SpiderWeb();
	~SpiderWeb();
	void Fire(MathHelper::Vector2F dir);
	bool getAttach() { return attach; }
	virtual void Update(float deltaTime) override;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget) override;

	virtual void OnBlock(Collider* pOtherComponent) override;
	virtual void OnBeginOverlap(Collider* pOtherComponent) override;
	virtual void OnEndOverlap(Collider* pOtherComponent) override;
};

