#pragma once
#include "Component.h"
#include "MathHelper.h"

class Transform;

class Movement :
    public Component
{
public:
	Movement(Transform* target); //�̰Ŵ� �����ڿ��� �־������. 
	virtual ~Movement() = default;
public:
	MathHelper::Vector2F	m_Velocity;		// �ӵ� ����
	Transform*				transform;		// ��ġ�� ������ ������Ʈ
	D2D_VECTOR_2F 			m_PrevRelativeLocation = { 0,0 }; // ���� ��ġ
public:
	virtual void Update(float deltaTime);
	//������ Ȱ��ȭ�ϸ� �����̴� �������� �����ֱ�?
	void SetSceneComponent(Transform* val) { transform = val; }
	void SetVelocity(MathHelper::Vector2F velocity) { m_Velocity = velocity; };
	void AddVelocity(MathHelper::Vector2F velocity) { m_Velocity += velocity; };
	void PrevPosition(bool prevX, bool prevY);
	MathHelper::Vector2F GetVelocity() { return m_Velocity; };
	MathHelper::Vector2F GetPrevPos() { return m_PrevRelativeLocation; };
};

