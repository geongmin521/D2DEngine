#pragma once
#include "IColliderNotify.h"

enum class CollisionType
{
	NoCollision,
	Block,
	Overlap
};

/*
	추상 클래스
*/
class Collider
{
public:
	Collider() = default;
	virtual ~Collider() = default;

protected:
	CollisionType m_CollisionType;		// 컬리전 타입 (노컬리전,블럭, 오버랩)
	D2D1_COLOR_F m_Color;				// 그리기용 색상
	IColliderNotify* notify;
	std::set<Collider*> m_CollideStateCurr;    // 현재 충돌 상태
	std::set<Collider*> m_CollideStatePrev;	// 이전 충돌 상태
public:

	CollisionType GetCollisionType() { return m_CollisionType; }
	void SetCollisionType(CollisionType Type) { m_CollisionType = Type; }

	D2D1_COLOR_F GetColor() const { return m_Color; }
	void SetColor(D2D1_COLOR_F val) { m_Color = val; }

	bool IsEmptyCollideStateCurr() { return m_CollideStateCurr.empty(); } //현재 충돌한 콜라이더가있는지 
	void InsertCollideState(Collider* pColliderComponent) { m_CollideStateCurr.insert(pColliderComponent); }

	void ClearAndBackupCollideState();
	void ProcessOverlap();
	virtual	void ProcessBlock(Collider* pOtherComponent); //충돌정보가 각자 다를것 같아서 상속으로 수정


	// Circle,Box 에서 각자 구현해야한다. //박스콜라이더가 이거랑 컴포넌트를 상속받아야할려나? 계속꼬여. 
	virtual bool IsCollide(Collider* pOtherComponent) = 0;
};

