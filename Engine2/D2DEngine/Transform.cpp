#include "pch.h"
#include "Transform.h"


Transform::Transform()
{
	m_RelativeTransform = m_WorldTransform = D2D1::Matrix3x2F::Identity();
}

Transform::~Transform()
{

}

void Transform::Update(float deltaTime)
{
	m_RelativeTransform = D2D1::Matrix3x2F::Scale(D2D1::SizeF(m_RelativeScale.x, m_RelativeScale.y)) *
		D2D1::Matrix3x2F::Rotation(m_RelativeRotation) *
		D2D1::Matrix3x2F::Translation(m_RelativeLocation.x, m_RelativeLocation.y);//역행렬에서.. 
	if (m_pParentScene != nullptr)
		m_WorldTransform = m_RelativeTransform * m_pParentScene->m_WorldTransform;
	else
		m_WorldTransform = m_RelativeTransform;
}


void Transform::SetRelativeRotation(float Rotation)
{
	m_RelativeRotation = Rotation;
	m_RelativeRotation = fmodf(m_RelativeRotation, 360.0f);
}

void Transform::AddRelativeRotation(float Rotation)
{
	m_RelativeRotation += Rotation;
	m_RelativeRotation = fmodf(m_RelativeRotation, 360.0f);
}


void Transform::SetRelativeLocation(const MathHelper::Vector2F& Location) //누군가 상대좌표를 이동시키면 즉시 월드 좌표에 적용될수있게하기
{
	m_RelativeLocation = Location;
	Update(1);// 델타타입은 의미없음
}

void Transform::AddRelativeLocation(float x, float y)
{
	m_RelativeLocation = { m_RelativeLocation.x + x,m_RelativeLocation.y + y };
}



