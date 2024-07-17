#pragma once
#include "Component.h"

class Renderer : public Component
{
public:
	bool m_bMirror;				// 좌우 반전 여부
	D2D1_MATRIX_3X2_F	m_ImageTransform;	// 반대 방향으로 뒤집기 위한 행렬 Scale.x = -1.0f  
	float CenterX;
	float CenterY;
	std::wstring m_strBitmapFilePath;
	ID2D1Bitmap* m_pBitmap = nullptr;
	D2D1_RECT_F m_DstRect;		// RenderTarget의 Destination 영역		

	Renderer(const std::wstring strFilePath);
	virtual ~Renderer();
	virtual void Update(float deltaTime) override;
	virtual void Render(ID2D1RenderTarget* pRenderTarget) override;
	void LoadD2DBitmap(const std::wstring strFilePath);

	void SetMirror(bool mirror) { m_bMirror = mirror; }
};

