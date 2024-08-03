#include "pch.h"
#include "AABB.h"
#include "Bitmap.h"

Bitmap::Bitmap(const std::wstring strFilePath) : Renderer(strFilePath) 
{
	DstRect.right = Bitmap->GetSize().width; 
	DstRect.bottom = Bitmap->GetSize().height; 
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
	assert(Bitmap != nullptr);
	__super::Render(pRenderTarget);
	pRenderTarget->DrawBitmap(Bitmap);
}

