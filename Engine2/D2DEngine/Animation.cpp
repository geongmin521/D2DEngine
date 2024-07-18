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
	// ���ҽ��Ŵ����� ���Ͽ� �����̸����� �����Ѵ�.
	if (m_pAnimationAsset)
	{
		//�� ������ ����ϴ� ��� ��ü�� ������� �����ϱ�
		//ResourceManager::pInstance->ReleaseAnimationAsset(m_strAnimationAssetFilePath);
		m_pAnimationAsset = nullptr;
	}
}

void Animation::LoadAnimationAsset(const std::wstring strFilePath)
{
	m_strAnimationAssetFilePath = strFilePath;
	ResourceManager::pInstance->CreateAnimationAsset(strFilePath, &m_pAnimationAsset);
}



void Animation::Update(float fTimeElapsed)	//��� ������Ʈ�� �ȿ� ����������������ֳ�? ����.. 
{
	__super::Update(fTimeElapsed);
	assert(m_pAnimationAsset != nullptr);
	if (m_pAnimationInfo == nullptr)
		return;
	
	const FRAME_INFO& Frame = m_pAnimationInfo->Frames[m_FrameIndexCurr];
	size_t MaxFrameCount = m_pAnimationInfo->Frames.size();

	m_FrameTime += fTimeElapsed;

	if (isLoop == false
		&& m_FrameIndexCurr == (MaxFrameCount - 1)   // ���� �������� ������ �������̶��
		&& m_FrameTime >= Frame.Duration)	// ���� �������� �ð��� Duration���� ũ�ٸ�
	{
		m_bAnimationEnd = true;
	}

	if (Frame.Duration < m_FrameTime)
	{
		m_FrameIndexCurr++;
		m_FrameTime = 0;
		if (m_pAnimationInfo->Frames.size() <= m_FrameIndexCurr)//������ �ƴϸ� �ٸ��� ó���ؾ��ҰŰ�����
		{
			m_FrameIndexCurr = 0; //�����϶��� �ִ뿡�� �������� �־��ֱ�.. 
		}
	}

	m_SrcRect = Frame.Source;
	m_DstRect = { 0,0,m_SrcRect.right - m_SrcRect.left,m_SrcRect.bottom - m_SrcRect.top };

	if (m_bMirror) //�̰͵� ���� ������ ����.. �׸��� ������Ʈ���� ó����������.. set���� �ϰ���µ�.. ������Ʈ���� ���⸸ �ٸ��� ����Ǹ�ǰڱ���.. 
	{
		m_ImageTransform = D2D1::Matrix3x2F::Scale(-1.0f, 1.0f, D2D1::Point2F(0, 0)) *
			D2D1::Matrix3x2F::Translation(m_DstRect.right - m_DstRect.left, 0);
	}
}

void Animation::Render(ID2D1RenderTarget* pRenderTarget) //������ �ϳ��� ������ڰ��߾��µ�.. ��� ���� ���̾ȿ���..  //�ϴ� �𸣰����� �Ұź�������.. 
{
	if (m_pAnimationInfo == nullptr)
		return;
	__super::Render(pRenderTarget);
	
	pRenderTarget->DrawBitmap(m_pBitmap, m_DstRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, m_SrcRect); //�׸����� �Ű��ִ°� �ƴ϶� ���ʿ� ������ġ�� �������� �׷��� �Űܾ��ϴ°žƴѰ�? 
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
