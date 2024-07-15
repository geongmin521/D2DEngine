
#pragma once
#include "Renderer.h"

class AnimationAsset;
struct ANIMATION_INFO;

class Animation :public Renderer
{
private:
	bool m_bAnimationEnd;

public:
	Animation(std::wstring bitmap, std::wstring animation);
	virtual ~Animation();
	bool isLoop = true;
	// �����ϴ� �ִϸ��̼� ����	
	AnimationAsset* m_pAnimationAsset = nullptr;  // �����ϴ� �ִϸ��̼� ����

	// �ν��Ͻ����� �ٸ� �ִϸ��̼� ����
	ANIMATION_INFO* m_pAnimationInfo = nullptr;	// ���� �ִϸ��̼� ������ ����
	std::wstring m_strAnimationAssetFilePath;    // �ִϸ��̼� ���� ���� ��
	float m_FrameTime = 0.0f;	// ������ ����ð�
	int m_FrameIndexCurr = -1;	// ���� ������ �ε���
	int m_FrameIndexPrev = -1;	// ���� ������ �ε���
	int m_AnimationIndex = -1;	// ���� �ִϸ��̼� �ε���
	D2D1_RECT_F m_SrcRect;		// D2D1Bitmap�� Source ����
	
	bool IsEnd() { return  m_bAnimationEnd; }
	void LoadAnimationAsset(const std::wstring strFilePath);
	virtual void Update(float fTimeElapsed) override;
	virtual void Render(ID2D1RenderTarget* pRenderTarget) override;
	void SetAnimation(int index, bool mirror);
	void Reverse(); 
};

