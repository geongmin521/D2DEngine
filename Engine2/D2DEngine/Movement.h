#pragma once
#include "Component.h"
#include "MathHelper.h"

class Transform;

class Movement :
    public Component
{
public:
	Movement(Transform* target, float Speed); //�̰Ŵ� �����ڿ��� �־������. 
	virtual ~Movement() = default;
	
protected:
	float			m_Speed = 0.0f;		// 1�ʴ� �̵��� �ӷ�
	bool			isBlock = false;		// �ݶ��̴��� ���� ������ Ȱ��ȭ
	MathHelper::Vector2F	m_Direction{ 0.0f,0.0f };	// ���� ���ֺ���
	MathHelper::Vector2F	m_Velocity;		// �ӵ� ����
	Transform* transform; // ��ġ�� ������ ������Ʈ
public:
	virtual void Update(float deltaTime);

	void SetSceneComponent(Transform* val) { transform = val; }
	void SetSpeed(float speed) { m_Speed = speed; };
	float GetSpeed() { return m_Speed; };
	virtual void SetDirection(const MathHelper::Vector2F& Direction);
	const MathHelper::Vector2F& GetDirection() { return m_Direction; };
};

