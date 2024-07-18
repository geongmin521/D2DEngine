#pragma once


class GameObject;
class Component
{
public:
	Component();
	virtual ~Component();

	GameObject* m_pOwner;

public:
	
	void SetOwner(GameObject* pOwner) { m_pOwner = pOwner; }

	virtual void Update(float deltaTime);
	virtual void Render(ID2D1RenderTarget* pRenderTarget);
};

//pch�� �׻����� �����������ʳ�?
//Ʈ������ aabb ���ӿ�����Ʈ ����� ���ΰŰ�����.. �̵��� ��������� ���������?