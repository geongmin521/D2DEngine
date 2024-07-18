#pragma once
#include "Component.h"

class Transform : public Component
{
private :
	//���⿡ ������������ ������ //������ ��ȯ�� �ܺο��� ���۾��ؾ��ҰŰ�����..
	//�ٵ��� �����ǥ�� �ʿ��ѰԾƴ϶�.. ���� ��ǥ�� �ʿ��ؼ�.. ���� ����� �غ����ҵ�
public:
	Transform();
	virtual ~Transform();
	Transform* m_pParentScene = nullptr;		// �θ� Scene ������Ʈ	
	D2D_VECTOR_2F		m_RelativeScale = { 1,1 };	// ��� ũ��
	float				m_RelativeRotation = 0; // ��� ȸ��
	D2D_VECTOR_2F 		m_RelativeLocation = { 0,0 }; // ��� ��ġ
	D2D_VECTOR_2F 		m_PrevRelativeLocation = { 0,0 }; // ��� ���� ��ġ
	D2D_MATRIX_3X2_F	m_RelativeTransform; // ��� ���� ��ȯ
	
	D2D_MATRIX_3X2_F	m_WorldTransform;    // �θ���� �ݿ��� ���� ��ȯ
	// RelativeTransform�� 	m_WorldTransform�� ����Ѵ�.
	virtual void Update(float deltaTime) override;
	void SetParent(Transform* pParentScene) { m_pParentScene = pParentScene; }

	D2D1_VECTOR_2F GetWorldLocation()
	{
		D2D1_VECTOR_2F out;
		out.x = m_WorldTransform._31;
		out.y = m_WorldTransform._32;
		return out;
	}

	void SetRelativeRotation(float Rotation);
	void AddRelativeRotation(float Rotation);
	float GetRelativeRotation() { return m_RelativeRotation; }

	void SetRelativeLocation(const D2D1_VECTOR_2F& Location);
	void AddRelativeLocation(float x, float y);
	const D2D1_VECTOR_2F& GetRelativeLocation() { return m_RelativeLocation; }
};
