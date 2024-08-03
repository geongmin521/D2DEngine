#include "pch.h"
#include "Transform.h"

Transform::Transform()
{
	relativeTransform = worldTransform = D2D1::Matrix3x2F::Identity();
}

Transform::~Transform()
{

}

void Transform::Update(float deltaTime)
{
	relativeTransform = D2D1::Matrix3x2F::Scale(D2D1::SizeF(relativeScale.x, relativeScale.y)) *
		D2D1::Matrix3x2F::Rotation(relativeRotation) *
		D2D1::Matrix3x2F::Translation(relativeLocation.x, relativeLocation.y);//역행렬에서.. 
	if (parentScene != nullptr)
		worldTransform = relativeTransform * parentScene->worldTransform;
	else
		worldTransform = relativeTransform;
}


void Transform::SetRelativeRotation(float Rotation)
{
	relativeRotation = Rotation;
	relativeRotation = fmodf(relativeRotation, 360.0f);
}

void Transform::AddRelativeRotation(float Rotation)
{
	relativeRotation += Rotation;
	relativeRotation = fmodf(relativeRotation, 360.0f);
}


void Transform::SetRelativeLocation(const MathHelper::Vector2F& Location) //누군가 상대좌표를 이동시키면 즉시 월드 좌표에 적용될수있게하기
{
	relativeLocation = Location;
	Update(1);// 델타타입은 의미없음
}

void Transform::AddRelativeLocation(float x, float y)
{
	relativeLocation = { relativeLocation.x + x,relativeLocation.y + y };
}

std::wstring Transform::ShowPos()
{
	
	return L"로컬좌표: " + std::to_wstring(relativeLocation.x) + L"  " + std::to_wstring(relativeLocation.y)
		+  L"절대좌표: " + std::to_wstring(GetWorldLocation().x) + L"  " + std::to_wstring(GetWorldLocation().y);
}



