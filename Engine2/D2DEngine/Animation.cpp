#include "pch.h"
#include "Animation.h"
#include "AnimationAsset.h"
#include "D2DRenderer.h"
#include "ResourceManager.h"

Animation::Animation(std::wstring bitmap, std::wstring animation): Renderer(bitmap) 
{
	LoadAnimationAsset(animation); 
	SetAnimation(0, false); 
}

Animation::~Animation()
{
	// 리소스매니저를 통하여 에셋이름으로 해제한다.
	if (m_pAnimationAsset)
	{
		//이 에셋을 사용하는 모든 객체가 사라지면 해제하기
		//ResourceManager::pInstance->ReleaseAnimationAsset(m_strAnimationAssetFilePath);
		m_pAnimationAsset = nullptr;
	}
}

void Animation::LoadAnimationAsset(const std::wstring strFilePath)
{
	m_strAnimationAssetFilePath = strFilePath;
	ResourceManager::pInstance->CreateAnimationAsset(strFilePath, &m_pAnimationAsset);
}



void Animation::Update(float fTimeElapsed)	//모든 컴포넌트에 안에 구현방식이있을수있나? 없지.. 
{
	__super::Update(fTimeElapsed);
	assert(m_pAnimationAsset != nullptr);
	if (m_pAnimationInfo == nullptr)
		return;
	
	const FRAME_INFO& Frame = m_pAnimationInfo->Frames[m_FrameIndexCurr];
	size_t MaxFrameCount = m_pAnimationInfo->Frames.size();

	m_FrameTime += fTimeElapsed;

	if (isLoop == false
		&& m_FrameIndexCurr == (MaxFrameCount - 1)   // 현재 프레임이 마지막 프레임이라면
		&& m_FrameTime >= Frame.Duration)	// 현재 프레임의 시간이 Duration보다 크다면
	{
		m_bAnimationEnd = true;
	}

	if (Frame.Duration < m_FrameTime)
	{
		m_FrameIndexCurr++;
		m_FrameTime = 0;
		if (m_pAnimationInfo->Frames.size() <= m_FrameIndexCurr)//루프가 아니면 다르게 처리해야할거같은데
		{
			m_FrameIndexCurr = 0; //루프일때만 최대에서 다음으로 넣어주기.. 
		}
	}

	m_SrcRect = Frame.Source;
	m_DstRect = { 0,0,m_SrcRect.right - m_SrcRect.left,m_SrcRect.bottom - m_SrcRect.top };

	if (m_bMirror) //이것도 공통 렌더로 빼자.. 그리고 업데이트에서 처리하지말고.. set에서 하고시픈데.. 업데이트에서 여기만 다르게 적용되면되겠구나.. 
	{
		m_ImageTransform = D2D1::Matrix3x2F::Scale(-1.0f, 1.0f, D2D1::Point2F(0, 0)) *
			D2D1::Matrix3x2F::Translation(m_DstRect.right - m_DstRect.left, 0);
	}
}

void Animation::Render(ID2D1RenderTarget* pRenderTarget) //렌더를 하나로 묶어놓자고했었는데.. 어떻게 할지 감이안오네..  //일단 모르겠으니 할거부터하자.. 
{
	if (m_pAnimationInfo == nullptr)
		return;
	__super::Render(pRenderTarget);
	
	pRenderTarget->DrawBitmap(m_pBitmap, m_DstRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, m_SrcRect); //그릴때만 옮겨주는게 아니라 애초에 시작위치의 포지션을 그렇게 옮겨야하는거아닌가? 
	pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}

void Animation::SetAnimation(int index, bool mirror)
{
	assert(m_pAnimationAsset != nullptr);

	ANIMATION_INFO* pFound = m_pAnimationAsset->GetAnimationInfo(index);
	if (pFound == nullptr)
		return;

	m_pAnimationInfo = pFound;
	m_bMirror = mirror;
	m_FrameIndexCurr = 0;
	m_FrameIndexPrev = 0;
	m_FrameTime = 0.0f;
	m_bAnimationEnd = false;
}

void Animation::Reverse()
{
	m_bMirror = !m_bMirror;
}
