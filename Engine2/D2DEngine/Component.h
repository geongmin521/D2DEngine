#pragma once


class GameObject;
class Component
{

private:
	bool isActive = true;
	virtual void Enable();	//isActive �� true�� �ɶ� ȣ��
	virtual void Disable();	//isActive �� false�� �ɶ� ȣ��
public:
	Component();
	virtual ~Component();

	GameObject* owner;

public:
	void setActive(bool active);
	bool getActive() { return isActive; }
	void SetOwner(GameObject* pOwner) { owner = pOwner; }

	virtual void Update(float deltaTime);
	virtual void Render(ID2D1RenderTarget* pRenderTarget);


};

//pch�� �׻����� �����������ʳ�?
//Ʈ������ aabb ���ӿ�����Ʈ ����� ���ΰŰ�����.. �̵��� ��������� ���������?