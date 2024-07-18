#pragma once
#include "../D2DEngine/GameObject.h"

//class AnimationScene;
class Character : //애는 컨턴츠에 대한 구현이고 데모앱에 들어있는게 맞지않나? 일단 구분을 잘모르겠으니 일단..걍 해보자..
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

