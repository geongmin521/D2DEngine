#pragma once
#include "../D2DEngine/GameObject.h"

class Missile :public GameObject 
{
public:
	float distance;
	float Timer;
	Transform* target;
	Missile();
	~Missile();
	virtual void Update(float deltaTime) override;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget) override;
};

