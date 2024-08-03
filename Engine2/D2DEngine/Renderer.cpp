#include "pch.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "D2DRenderer.h"
#include "Transform.h"
Renderer::Renderer(const std::wstring strFilePath)
{
	LoadD2DBitmap(strFilePath);
}

Renderer::~Renderer()
{
	/*
	if (Bitmap)
	{
		Bitmap->Release();
		Bitmap = nullptr;
	}
	*/
	if (Bitmap)
	{
		ResourceManager::Instance->ReleaseD2DBitmap(strBitmapFilePath);
		Bitmap = nullptr;
	}
}

void Renderer::Update(float deltaTime)
{
	if (mirror) 
	{
		imageTransform = D2D1::Matrix3x2F::Scale(-1.0f, 1.0f, D2D1::Point2F(0, 0)) *
			D2D1::Matrix3x2F::Translation(-CenterX, CenterY); 
	}
	else
	{
		imageTransform = D2D1::Matrix3x2F::Scale(1.0f, 1.0f, D2D1::Point2F(0, 0)) * 
			D2D1::Matrix3x2F::Translation(CenterX, CenterY);
	}
}

void Renderer::Render(ID2D1RenderTarget* pRenderTarget) //어디그릴지에 대한 계산은 여기서 통일하기
{
	float CenterX = -(DstRect.right - DstRect.left) / 2 * owner->m_Transform->relativeScale.x;
	float CenterY = -(DstRect.bottom - DstRect.top) / 2 * owner->m_Transform->relativeScale.y;

	D2D1_MATRIX_3X2_F Transform = imageTransform * owner->m_Transform->worldTransform 
		* D2DRenderer::cameraTransform * D2D1::Matrix3x2F::Translation(CenterX, CenterY);

	pRenderTarget->SetTransform(Transform);
}

void Renderer::LoadD2DBitmap(const std::wstring strFilePath)
{
	ResourceManager::Instance->CreateD2DBitmapFromFile(strFilePath, &Bitmap);
	strBitmapFilePath = strFilePath;
}