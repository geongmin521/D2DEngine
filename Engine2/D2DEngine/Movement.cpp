#include "pch.h"
#include "Movement.h"
#include "Transform.h"

Movement::Movement(Transform* target, float Speed) : m_Speed(Speed)
{
	transform = target;
}

// 가속도 개념없이 일정한 속도로 이동한다.
void Movement::Update(float DeltaTime) //오케이 리지드 바디 쓸일이있을까? 그냥 무브먼트에 넣어놓는게어떰.. 
{
	m_PrevRelativeLocation = transform->m_RelativeLocation;

	//if (isGravity) //절대 좌표계에서 움직이는게 맞지않을까?
	//transform->m_RelativeLocation.y += 9.8; //밑으로떨어지려면.. + 지?
	// 현재 위치를 가져온다.
	MathHelper::Vector2F Location = transform->GetRelativeLocation();
	m_Velocity = m_Direction * m_Speed;

	// 새로운 위치를 계산한다.
	Location += m_Velocity * DeltaTime;

	//중력에 의한 위치
	Location += MathHelper::Vector2F(0, 1) * 98.0f * DeltaTime * 3; //센터랑하나?
	//새로 계산된 위치를 적용한다.
	transform->SetRelativeLocation(Location);
}

void Movement::PrevPosition()// aabb는 4방향으로 충돌이 가능하단 말이여.. 
{
	//y가 이전위치로 갈때랑 x가 이전위치로 갈때랑 다양하게 있을수있을텐데.. 그것들을어떻게 구분해야할까.. 
	//y를 위로 가고... 
	// transform->m_RelativeLocation.y = m_PrevRelativeLocation.y; //콜라이더좀 다들 그려야겠네.. 
	 transform->m_RelativeLocation = m_PrevRelativeLocation; 
}

void Movement::SetDirection(const MathHelper::Vector2F& Direction)
{ 
	m_Direction = Direction;
	m_Direction.Normalize();
}


