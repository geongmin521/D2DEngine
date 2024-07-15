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
	if (m_pBitmap)
	{
		m_pBitmap->Release();
		m_pBitmap = nullptr;
	}
	*/
	if (m_pBitmap)
	{
		ResourceManager::pInstance->ReleaseD2DBitmap(m_strBitmapFilePath);
		m_pBitmap = nullptr;
	}
}

void Renderer::Update(float deltaTime)
{
	if (m_bMirror) 
	{
		m_ImageTransform = D2D1::Matrix3x2F::Scale(-1.0f, 1.0f, D2D1::Point2F(0, 0)) *
			D2D1::Matrix3x2F::Translation(-CenterX, CenterY); 
	}
	else
	{
		m_ImageTransform = D2D1::Matrix3x2F::Scale(1.0f, 1.0f, D2D1::Point2F(0, 0)) * 
			D2D1::Matrix3x2F::Translation(CenterX, CenterY);
	}
}

void Renderer::Render(ID2D1RenderTarget* pRenderTarget) //어디그릴지에 대한 계산은 여기서 통일하기
{
	float CenterX = -(m_DstRect.right - m_DstRect.left) / 2 * m_pOwner->m_Transform->m_RelativeScale.x;
	float CenterY = -(m_DstRect.bottom - m_DstRect.top) / 2 * m_pOwner->m_Transform->m_RelativeScale.y;

	D2D1_MATRIX_3X2_F Transform = m_ImageTransform * m_pOwner->m_Transform->m_WorldTransform 
		* D2DRenderer::m_CameraTransform * D2D1::Matrix3x2F::Translation(CenterX, CenterY);

	pRenderTarget->SetTransform(Transform);
}

void Renderer::LoadD2DBitmap(const std::wstring strFilePath)
{
	ResourceManager::pInstance->CreateD2DBitmapFromFile(strFilePath, &m_pBitmap);
	m_strBitmapFilePath = strFilePath;
}