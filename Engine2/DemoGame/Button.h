#pragma once
#include "UI.h"
class Button: public UI //�巡�� ���̺� ��� ���̺� ���� ��ӹް��ϰ�... Ŭ�� ��Ƽ�ǵ� �����.. �������̽��� ��ӹް��ִ� ��� 
	//�ɼ��� ������ �Ǵ°ǰ�? �Է� ��������.. �Է¹ޱ�.. 
{
private:

public:
	Button();
	~Button();
	virtual void Update(float deltaTime) override;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget) override;
};

