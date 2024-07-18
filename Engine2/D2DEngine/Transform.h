#pragma once
#include "Component.h"

class Transform : public Component
{
private :
	//여기에 월드포지션을 넣을까 //월드의 변환은 외부에서 조작안해야할거같은데..
	//근데또 상대좌표만 필요한게아니라.. 월드 좌표도 필요해서.. 좀더 고민을 해봐야할듯
public:
	Transform();
	virtual ~Transform();
	Transform* m_pParentScene = nullptr;		// 부모 Scene 컴포넌트	
	D2D_VECTOR_2F		m_RelativeScale = { 1,1 };	// 상대 크기
	float				m_RelativeRotation = 0; // 상대 회전
	D2D_VECTOR_2F 		m_RelativeLocation = { 0,0 }; // 상대 위치
	D2D_VECTOR_2F 		m_PrevRelativeLocation = { 0,0 }; // 상대 이전 위치
	D2D_MATRIX_3X2_F	m_RelativeTransform; // 상대 복합 변환
	
	D2D_MATRIX_3X2_F	m_WorldTransform;    // 부모까지 반영된 최종 변환
	// RelativeTransform과 	m_WorldTransform을 계산한다.
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
