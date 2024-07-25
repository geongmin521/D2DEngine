#include "pch.h"
#include "AABB.h"
#include "Bitmap.h"

Bitmap::Bitmap(const std::wstring strFilePath) : Renderer(strFilePath) 
{
	m_DstRect.right = m_pBitmap->GetSize().width; 
	m_DstRect.bottom = m_pBitmap->GetSize().height; 
}

Bitmap::~Bitmap() 
{

}


void Bitmap::Update(float fTimeElapsed)
{
	__super::Update(fTimeElapsed);
}

void Bitmap::Render(ID2D1RenderTarget* pRenderTarget)  
{
	assert(m_pBitmap != nullptr);
	__super::Render(pRenderTarget);
	pRenderTarget->DrawBitmap(m_pBitmap);
}

