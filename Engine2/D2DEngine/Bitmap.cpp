#include "pch.h"
#include "AABB.h"
#include "Bitmap.h"

Bitmap::Bitmap(const std::wstring strFilePath) : Renderer(strFilePath) 
{
	//단순히 위치를 뺀 높이와 너비면 충분
	m_DstRect.right = m_pBitmap->GetSize().width; //남의 구조에 오퍼레이터를 만들수있나? 
	m_DstRect.bottom = m_pBitmap->GetSize().height; //남의 구조에 오퍼레이터를 만들수있나? 
	//아니면 포멧을 만들어야하나?
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

