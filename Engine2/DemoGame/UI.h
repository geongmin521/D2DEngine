#pragma once
#include "../D2DEngine/GameObject.h"

class UI : public GameObject //UI�� ���� ������Ʈ�� ����������.. UI �̺�Ʈ �ý����� ���ؼ�.. ���콺 �̺�Ʈ�� �Է¹޴°ɷ�����.. //�׸��� Ư�� UI�� ���� ������ �� �ߵ���
{
public:
	UI();
	~UI();
	virtual void Update(float deltaTime) override;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget) override;
};

