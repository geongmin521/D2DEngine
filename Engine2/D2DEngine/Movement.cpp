#include "pch.h"
#include "Movement.h"
#include "Transform.h"

Movement::Movement(Transform* target, bool isgravity) : isGravity(isgravity)
{
	m_Velocity = { 0,0 };
	transform = target;
}


void Movement::Update(float DeltaTime) //무브먼트가 독립적인 힘여러개가 합쳐지는형식으로 만드는게 더 나을듯? 
{
	m_PrevRelativeLocation = transform->GetRelativeLocation(); //이거 값복사일어나는거맞지?

	MathHelper::Vector2F Location = m_PrevRelativeLocation;
	if(isGravity)
		m_Velocity += (MathHelper::Vector2F(0, 1) * 98.0f);

	Location += m_Velocity * DeltaTime; //변화량을 정확하게알아야지.. 

	transform->SetRelativeLocation(Location);
}

void Movement::PrevPosition(bool prevX, bool prevY)// aabb는 4방향으로 충돌이 가능하단 말이여.. 
{
	if (prevX)
	{
		transform->m_RelativeLocation.x = m_PrevRelativeLocation.x;
	}
	if (prevY)
	{
		m_Velocity.y = 0;
		transform->m_RelativeLocation.y = m_PrevRelativeLocation.y;
	}
	 
}



