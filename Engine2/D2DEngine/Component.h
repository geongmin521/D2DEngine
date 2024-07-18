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

//pch가 항상위면 생기지않지않나?
//트랜스폼 aabb 게임오브젝트 헤더가 꼬인거같은데.. 이들의 순서관계는 상관없겠지?