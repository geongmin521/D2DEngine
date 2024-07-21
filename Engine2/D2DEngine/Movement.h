#pragma once
#include "Component.h"
#include "MathHelper.h"

class Transform;

class Movement :
    public Component
{
public:
	Movement(Transform* target,bool isgravity = false); //�̰Ŵ� �����ڿ��� �־������. 
	virtual ~Movement() = default;
	
public:

	MathHelper::Vector2F	m_Velocity;		// �ӵ� ����
	Transform* transform; // ��ġ�� ������ ������Ʈ
	D2D_VECTOR_2F 		m_PrevRelativeLocation = { 0,0 }; // ��� ��ġ
	bool isGravity = false;

public:
	virtual void Update(float deltaTime);
	void SetSceneComponent(Transform* val) { transform = val; }
	//void SetSpeed(float speed) { m_Speed = speed; };
	//float GetSpeed() { return m_Speed; };
	MathHelper::Vector2F GetVelocity() { return m_Velocity; };
	void SetVelocity(MathHelper::Vector2F velocity) { m_Velocity = velocity; };
	void AddVelocity(MathHelper::Vector2F velocity) { m_Velocity += velocity; };
	D2D_VECTOR_2F GetPrevPos() { return m_PrevRelativeLocation; }; //Ʃ�÷� �����ͺ���?
	void PrevPosition(bool prevX, bool prevY);

	//virtual void SetDirection(const MathHelper::Vector2F& Direction);
	//const MathHelper::Vector2F& GetDirection() { return m_Direction; };
};

