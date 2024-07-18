#include "pch.h"
#include "Movement.h"
#include "Transform.h"

Movement::Movement(Transform* target, float Speed) : m_Speed(Speed)
{
	transform = target;
}

// 가속도 개념없이 일정한 속도로 이동한다.
void Movement::Update(float DeltaTime)
{
	if (isBlock[0])//위쪽 막힘 
		MathHelper::Clamp<float>(m_Direction.y, 0, -1);
	if (isBlock[1])//아래쪽
		MathHelper::Clamp<float>(m_Direction.y, 1, 0);
	if (isBlock[2])//왼쪽
		MathHelper::Clamp<float>(m_Direction.x, 1, 0);
	if (isBlock[3])//오른쪽
		MathHelper::Clamp<float>(m_Direction.x,-1, 0);

	// 현재 위치를 가져온다.
	MathHelper::Vector2F Location = transform->GetRelativeLocation();
	m_Velocity = m_Direction * m_Speed;

	// 새로운 위치를 계산한다.
	Location += m_Velocity * DeltaTime;

	//새로 계산된 위치를 적용한다.
	transform->SetRelativeLocation(Location);
}

void Movement::SetDirection(const MathHelper::Vector2F& Direction)
{ 
	m_Direction = Direction;
	m_Direction.Normalize();
}


