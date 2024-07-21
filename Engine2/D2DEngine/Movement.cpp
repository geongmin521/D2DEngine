#include "pch.h"
#include "Movement.h"
#include "Transform.h"

Movement::Movement(Transform* target, bool isgravity) : isGravity(isgravity)
{
	m_Velocity = { 0,0 };
	transform = target;
}


void Movement::Update(float DeltaTime) //�����Ʈ�� �������� ���������� ���������������� ����°� �� ������? 
{
	m_PrevRelativeLocation = transform->GetRelativeLocation(); //�̰� �������Ͼ�°Ÿ���?

	MathHelper::Vector2F Location = m_PrevRelativeLocation;
	if(isGravity)
		m_Velocity += (MathHelper::Vector2F(0, 1) * 98.0f);

	Location += m_Velocity * DeltaTime; //��ȭ���� ��Ȯ�ϰԾ˾ƾ���.. 

	transform->SetRelativeLocation(Location);
}

void Movement::PrevPosition(bool prevX, bool prevY)// aabb�� 4�������� �浹�� �����ϴ� ���̿�.. 
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



