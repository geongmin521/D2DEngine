#include "pch.h"
#include "Transform.h"
#include "D2DRenderer.h"
#include "RigidBody.h"
#include "AABB.h"

RigidBody::RigidBody(Transform* transform, bool isGravity )
{
	this->isGravity = isGravity;
	tr = transform;
	GravityScale = 9.8;
}

RigidBody::~RigidBody()
{
}

void RigidBody::Update(float deltaTime)
{
	if (isGravity) //절대 좌표계에서 움직이는게 맞지않을까?
		tr->m_WorldTransform.dy += GravityScale; //밑으로떨어지려면.. + 지?
}

void RigidBody::Render(ID2D1RenderTarget* pRenderTarget, D2D1_MATRIX_3X2_F transform)
{
	D2DRenderer::GetInstance()->DrawBox(
		aabb->GetMinX(),
		aabb->GetMaxY(),
		aabb->GetMaxX(),
		aabb->GetMinY());
}
