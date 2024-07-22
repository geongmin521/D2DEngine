#include "pch.h"
#include "Transform.h"
#include "D2DRenderer.h"
#include "RigidBody.h"
#include "AABB.h"

RigidBody::RigidBody()
{
	Enable();
}

RigidBody::~RigidBody()
{
}

void RigidBody::Update(float deltaTime)
{
	if (isGravity)
		GravityScale += 0.098; //�߷°��ӵ��� ��Ӵ����� ��ŸŸ���� �����Ʈ���� ����������
}

void RigidBody::Enable()
{
	isGravity = true;
	GravityScale = 0;
}

void RigidBody::Disable()
{
	GravityScale = 0;
}

