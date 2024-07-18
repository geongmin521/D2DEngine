#pragma once
#include "Component.h"
#include "MathHelper.h"

class Transform;

class Movement :
    public Component
{
public:
	Movement(Transform* target, float Speed); //이거는 생성자에서 넣어줘야지. 
	virtual ~Movement() = default;
	
protected:
	float			m_Speed = 0.0f;		// 1초당 이동할 속력
	
	MathHelper::Vector2F	m_Direction{ 0.0f,0.0f };	// 방향 유닛벡터
	MathHelper::Vector2F	m_Velocity;		// 속도 벡터
	Transform* transform; // 위치를 변경할 컴포넌트
	D2D_VECTOR_2F 		m_PrevRelativeLocation = { 0,0 }; // 상대 위치
	//D2D_VECTOR_2F 		m_RelativeLocation = { 0,0 }; // 상대 위치 이전위치로 보내는건가? 
	//아니지 방향만 0으로 만들어야지.. 문제는 물체가빠를수록 오차범위가 커진다는건데.. 일단 해보고 바꿔볼까? 
	//제일 정확한거는 접촉점의 들어간 깊이를 파악해서 그만큼 올려주는게 제일 정확하지 속도의 영향도 안받고.. 
public:
	virtual void Update(float deltaTime);
	bool			isBlock[4] = { false,false,false,false };//위, 아래, 왼쪽, 오른쪽 // 콜라이더에 의해 막히면 활성화
	void SetSceneComponent(Transform* val) { transform = val; }
	void SetSpeed(float speed) { m_Speed = speed; };
	float GetSpeed() { return m_Speed; };
	void PrevPosition();
	virtual void SetDirection(const MathHelper::Vector2F& Direction);
	const MathHelper::Vector2F& GetDirection() { return m_Direction; };
};

