#include "pch.h"
#include "ResourceManager.h"
#include "AnimationAsset.h"
#include "D2DRenderer.h"

ResourceManager::ResourceManager()
{
	ResourceManager::Instance = this;
}

ResourceManager::~ResourceManager() 
{
	assert(m_BitmapMap.empty());
	assert(animationAssetMap.empty());
}

ResourceManager* ResourceManager::Instance = nullptr;

bool ResourceManager::CreateD2DBitmapFromFile(std::wstring strFilePath, ID2D1Bitmap** bitmap)
{
	if (m_BitmapMap.find(strFilePath) != m_BitmapMap.end()) 
	{
		*bitmap = m_BitmapMap[strFilePath];
		(*bitmap)->AddRef();
		return true;
	}
	ID2D1Bitmap* bmp;
	NewBitmapFromFile(strFilePath.c_str(), &bmp);
	m_BitmapMap[strFilePath] = bmp;		
	*bitmap = m_BitmapMap[strFilePath]; 
	(*bitmap)->AddRef();
	return true;
}

void ResourceManager::ReleaseD2DBitmap(std::wstring strFilePath)
{
	std::map<std::wstring, ID2D1Bitmap*>::iterator iter = m_BitmapMap.find(strFilePath);
	assert(iter != m_BitmapMap.end());

	if (iter != m_BitmapMap.end())
	{
		ID2D1Bitmap* bitmap = m_BitmapMap[strFilePath];
		if (bitmap->Release() == 0)
		{
			m_BitmapMap.erase(iter);
		}		
	}
}

bool ResourceManager::CreateAnimationAsset(std::wstring strFilePath, AnimationAsset** asset)
{
	if (animationAssetMap.find(strFilePath) != animationAssetMap.end())
	{
		*asset = animationAssetMap[strFilePath];
		(*asset)->AddRef();
		return true;
	} 
	AnimationAsset* pTemp = new AnimationAsset;	
	// ������ �ִϸ��̼� ���¿� �ִϸ��̼� �����͸� �ε��Ѵ�.
	if (pTemp->LoadAnimation(strFilePath) == false)
	{
		delete pTemp;	
		return false;
	}
	else
	{
		*asset = pTemp;
	}
	// ������ �ִϸ��̼� ������ �ʿ� �����Ѵ�.
	animationAssetMap[strFilePath] = *asset;
	return true;
}

void ResourceManager::ReleaseAnimationAsset(std::wstring strFilePath) 
{
	// �ʿ� �ش� Ű�� �����ϸ� �ִϸ��̼� ������ �����Ѵ�.
	std::map<std::wstring, AnimationAsset*>::iterator iter = animationAssetMap.find(strFilePath);
	assert(iter != animationAssetMap.end()); // �����̳ʿ� ������ Create/Release ¦�� �߸��ƴ�.

	if (iter != animationAssetMap.end())
	{
		AnimationAsset* asset = animationAssetMap[strFilePath];
		if (asset->Release() == 0)
		{
			animationAssetMap.erase(iter);
		}
	}
}

HRESULT ResourceManager::NewBitmapFromFile(const WCHAR * szFilePath, ID2D1Bitmap * *ppID2D1Bitmap)
{
	HRESULT hr;
	IWICBitmapDecoder* pDecoder = NULL;
	IWICFormatConverter* pConverter = NULL;

	hr = D2DRenderer::GetInstance()->WICFactory->CreateDecoderFromFilename(
		szFilePath,                      // Image to be decoded
		NULL,                            // Do not prefer a particular vendor
		GENERIC_READ,                    // Desired read access to the file
		WICDecodeMetadataCacheOnDemand,  // Cache metadata when needed
		&pDecoder                        // Pointer to the decoder
	);

	// Retrieve the first frame of the image from the decoder
	IWICBitmapFrameDecode* pFrame = NULL;
	if (SUCCEEDED(hr))
	{
		hr = pDecoder->GetFrame(0, &pFrame);
	}

	//Step 3: Format convert the frame to 32bppPBGRA
	if (SUCCEEDED(hr))
	{
		hr = D2DRenderer::GetInstance()->WICFactory->CreateFormatConverter(&pConverter);
	}

	if (SUCCEEDED(hr))
	{
		hr = pConverter->Initialize(
			pFrame,                          // Input bitmap to convert
			GUID_WICPixelFormat32bppPBGRA,   // Destination pixel format
			WICBitmapDitherTypeNone,         // Specified dither pattern
			NULL,                            // Specify a particular palette 
			0.f,                             // Alpha threshold
			WICBitmapPaletteTypeCustom       // Palette translation type
		);
	}

	if (SUCCEEDED(hr))
	{
		hr = D2DRenderer::GetInstance()->RenderTarget->CreateBitmapFromWicBitmap(pConverter, NULL, ppID2D1Bitmap);
	}
	// ������ ����Ҷ����� �ٽ� �����.
	if (pConverter)
		pConverter->Release();

	if (pDecoder)
		pDecoder->Release();

	if (pFrame)
		pFrame->Release();

	return hr;
}
