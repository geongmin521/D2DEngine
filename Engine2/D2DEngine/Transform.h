#pragma once
#include "Component.h"


class Transform : public Component
{
private :
	
public:
	Transform();
	virtual ~Transform();
	Transform* m_pParentScene = nullptr;		// �θ� Scene ������Ʈ	
	MathHelper::Vector2F m_RelativeScale = { 1,1 };	// ��� ũ��
	MathHelper::Vector2F m_RelativeLocation = { 0,0 }; // ��� ��ġ //�̰͵� �Ž� ���۷� ���ξȵǳ�? 
	D2D_MATRIX_3X2_F	 m_RelativeTransform; // ��� ���� ��ȯ						 
	D2D_MATRIX_3X2_F	 m_WorldTransform;    // �θ���� �ݿ��� ���� ��ȯ
	float	m_RelativeRotation = 0; // ��� ȸ��
	// RelativeTransform�� 	m_WorldTransform�� ����Ѵ�.
	virtual void Update(float deltaTime) override;
	void SetParent(Transform* pParentScene) { m_pParentScene = pParentScene; }

	MathHelper::Vector2F GetWorldLocation()
	{
		D2D1_VECTOR_2F out;
		out.x = m_WorldTransform._31;
		out.y = m_WorldTransform._32;
		return out;
	}

	void SetRelativeRotation(float Rotation);
	void AddRelativeRotation(float Rotation);
	float GetRelativeRotation() { return m_RelativeRotation; }

	void SetRelativeLocation(const MathHelper::Vector2F& Location);
	void AddRelativeLocation(float x, float y);
	const MathHelper::Vector2F& GetRelativeLocation() { return m_RelativeLocation; }

	std::wstring ShowPos();
};
