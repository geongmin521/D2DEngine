#pragma once
#include "../D2DEngine/WinGameApp.h" //�� ���� �̰Ŷ����ΰ�?

class DemoGameApp : public WinGameApp 
{

public: 
	virtual void Initialize(HINSTANCE hInstance, int nShowCmd) override;
	virtual void Run() override;
	virtual void Uninitialize() override;
	void Update(float fTimeElapsed);
	void Render(ID2D1HwndRenderTarget* pRenderTarget);
};
