#include "pch.h"
#include "Movement.h"
#include "Transform.h"

Movement::Movement(Transform* target)
{
	m_Velocity = { 0,0 };
	transform = target;
}

void Movement::Update(float DeltaTime) 
{
	m_PrevRelativeLocation = transform->GetRelativeLocation(); 
	MathHelper::Vector2F Location = m_PrevRelativeLocation;
	Location += m_Velocity * DeltaTime; 
	transform->SetRelativeLocation(Location);
}

void Movement::PrevPosition(bool prevX, bool prevY)
{
	if (prevX) transform->m_RelativeLocation.x = m_PrevRelativeLocation.x;	
	if (prevY) transform->m_RelativeLocation.y = m_PrevRelativeLocation.y;
}



