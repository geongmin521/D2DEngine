#pragma once
#include "Component.h"


class Transform : public Component
{
private :
	
public:
	Transform();
	virtual ~Transform();
	Transform* m_pParentScene = nullptr;		// 부모 Scene 컴포넌트	
	MathHelper::Vector2F m_RelativeScale = { 1,1 };	// 상대 크기
	MathHelper::Vector2F m_RelativeLocation = { 0,0 }; // 상대 위치 //이것도 매스 헬퍼로 매핑안되나? 
	D2D_MATRIX_3X2_F	 m_RelativeTransform; // 상대 복합 변환						 
	D2D_MATRIX_3X2_F	 m_WorldTransform;    // 부모까지 반영된 최종 변환
	float	m_RelativeRotation = 0; // 상대 회전
	// RelativeTransform과 	m_WorldTransform을 계산한다.
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
