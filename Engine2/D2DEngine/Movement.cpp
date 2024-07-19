#include "pch.h"
#include "Movement.h"
#include "Transform.h"

Movement::Movement(Transform* target, float Speed) : m_Speed(Speed)
{
	transform = target;
}

// ���ӵ� ������� ������ �ӵ��� �̵��Ѵ�.
void Movement::Update(float DeltaTime) //������ ������ �ٵ� ������������? �׳� �����Ʈ�� �־���°Ծ.. 
{
	m_PrevRelativeLocation = transform->m_RelativeLocation;

	//if (isGravity) //���� ��ǥ�迡�� �����̴°� ����������?
	//transform->m_RelativeLocation.y += 9.8; //�����ζ���������.. + ��?
	// ���� ��ġ�� �����´�.
	MathHelper::Vector2F Location = transform->GetRelativeLocation();
	m_Velocity = m_Direction * m_Speed;

	// ���ο� ��ġ�� ����Ѵ�.
	Location += m_Velocity * DeltaTime;

	//�߷¿� ���� ��ġ
	Location += MathHelper::Vector2F(0, 1) * 98.0f * DeltaTime * 3; //���Ͷ��ϳ�?
	//���� ���� ��ġ�� �����Ѵ�.
	transform->SetRelativeLocation(Location);
}

void Movement::PrevPosition()// aabb�� 4�������� �浹�� �����ϴ� ���̿�.. 
{
	//y�� ������ġ�� ������ x�� ������ġ�� ������ �پ��ϰ� �����������ٵ�.. �װ͵������ �����ؾ��ұ�.. 
	//y�� ���� ����... 
	// transform->m_RelativeLocation.y = m_PrevRelativeLocation.y; //�ݶ��̴��� �ٵ� �׷��߰ڳ�.. 
	 transform->m_RelativeLocation = m_PrevRelativeLocation; 
}

void Movement::SetDirection(const MathHelper::Vector2F& Direction)
{ 
	m_Direction = Direction;
	m_Direction.Normalize();
}


