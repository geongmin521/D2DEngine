#include "pch.h"
#include "Movement.h"
#include "Transform.h"

Movement::Movement(Transform* target, float Speed) : m_Speed(Speed)
{
	transform = target;
}

// ���ӵ� ������� ������ �ӵ��� �̵��Ѵ�.
void Movement::Update(float DeltaTime)
{
	if (isBlock == true)
		return;
	//transform.
	// ���� ��ġ�� �����´�.
	MathHelper::Vector2F Location = transform->GetRelativeLocation();
	m_Velocity = m_Direction * m_Speed;

	// ���ο� ��ġ�� ����Ѵ�.
	Location += m_Velocity * DeltaTime;

	//���� ���� ��ġ�� �����Ѵ�.
	transform->SetRelativeLocation(Location);
}

void Movement::SetDirection(const MathHelper::Vector2F& Direction)
{ 
	m_Direction = Direction;
	m_Direction.Normalize();
}


