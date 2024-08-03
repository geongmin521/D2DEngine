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
	MathHelper::Vector2F	velocity;		// �ӵ� ����
	Transform*				transform;		// ��ġ�� ������ ������Ʈ
	D2D_VECTOR_2F 			prevRelativeLocation = { 0,0 }; // ���� ��ġ
public:
	virtual void Update(float deltaTime);
	//������ Ȱ��ȭ�ϸ� �����̴� �������� �����ֱ�?
	void SetSceneComponent(Transform* val) { transform = val; }
	void SetVelocity(MathHelper::Vector2F velocity) { velocity = velocity; };
	void AddVelocity(MathHelper::Vector2F velocity) { velocity += velocity; };
	void PrevPosition(bool prevX, bool prevY);
	MathHelper::Vector2F GetVelocity() { return velocity; };
	MathHelper::Vector2F GetPrevPos() { return prevRelativeLocation; };
};

