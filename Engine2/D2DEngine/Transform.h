#pragma once
#include "Component.h"


class Transform : public Component
{
private :
	
public:
	Transform();
	virtual ~Transform();
	Transform* parentScene = nullptr;		// �θ� Scene ������Ʈ	
	MathHelper::Vector2F relativeScale = { 1,1 };	// ��� ũ��
	MathHelper::Vector2F relativeLocation = { 0,0 }; // ��� ��ġ //�̰͵� �Ž� ���۷� ���ξȵǳ�? 
	D2D1_POINT_2F imageCenter = { 0,0 }; // ��� ��ġ //�̰͵� �Ž� ���۷� ���ξȵǳ�? 
	D2D_MATRIX_3X2_F	 relativeTransform; // ��� ���� ��ȯ						 
	D2D_MATRIX_3X2_F	 worldTransform;    // �θ���� �ݿ��� ���� ��ȯ
	float	relativeRotation = 0; // ��� ȸ��
	// RelativeTransform�� 	worldTransform�� ����Ѵ�.
	virtual void Update(float deltaTime) override;
	void SetParent(Transform* pParentScene) { parentScene = pParentScene; }
	void SetImageCenter(D2D1_POINT_2F center) { this->imageCenter = center; }

	MathHelper::Vector2F GetWorldLocation()
	{
		D2D1_VECTOR_2F out;
		out.x = worldTransform._31;
		out.y = worldTransform._32;
		return out;
	}

	void SetRelativeRotation(float Rotation);
	void AddRelativeRotation(float Rotation);
	float GetRelativeRotation() { return relativeRotation; }

	void SetRelativeLocation(const MathHelper::Vector2F& Location);
	void AddRelativeLocation(float x, float y);
	const MathHelper::Vector2F& GetRelativeLocation() { return relativeLocation; }

	std::wstring ShowPos();
};
