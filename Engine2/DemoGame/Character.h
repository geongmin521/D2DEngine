#pragma once
#include "../D2DEngine/GameObject.h"

//class AnimationScene;
class Character : //�ִ� �������� ���� �����̰� ����ۿ� ����ִ°� �����ʳ�? �ϴ� ������ �߸𸣰����� �ϴ�..�� �غ���..
    public GameObject
{
private:
	float speed;
public:
	Character();
	virtual ~Character();	
	virtual void Update(float deltaTime);
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);
};

