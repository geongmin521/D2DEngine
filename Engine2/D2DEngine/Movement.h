#pragma once
#include "Component.h"
#include "MathHelper.h"

class Transform;

class Movement :
    public Component
{
public:
	Movement(Transform* target,bool isgravity = false); //이거는 생성자에서 넣어줘야지. 
	virtual ~Movement() = default;
	
public:

	MathHelper::Vector2F	m_Velocity;		// 속도 벡터
	Transform* transform; // 위치를 변경할 컴포넌트
	D2D_VECTOR_2F 		m_PrevRelativeLocation = { 0,0 }; // 상대 위치
	bool isGravity = false;

public:
	virtual void Update(float deltaTime);
	void SetSceneComponent(Transform* val) { transform = val; }
	//void SetSpeed(float speed) { m_Speed = speed; };
	//float GetSpeed() { return m_Speed; };
	MathHelper::Vector2F GetVelocity() { return m_Velocity; };
	void SetVelocity(MathHelper::Vector2F velocity) { m_Velocity = velocity; };
	void AddVelocity(MathHelper::Vector2F velocity) { m_Velocity += velocity; };
	D2D_VECTOR_2F GetPrevPos() { return m_PrevRelativeLocation; }; //튜플로 가져와볼까?
	void PrevPosition(bool prevX, bool prevY);

	//virtual void SetDirection(const MathHelper::Vector2F& Direction);
	//const MathHelper::Vector2F& GetDirection() { return m_Direction; };
};

