#pragma once
#include "Component.h"

enum class CollisionType
{
	NoCollision,
	Block,
	Overlap
};

enum class CollisionDir
{
	Top,
	Bottom,
	Left,
	Right
};

struct CollisionInfo //AABB에서의 충돌정보 이거는 그러면 박스 콜라이더로 내려야할듯? 
{
	CollisionDir dir;
	float depth;
	CollisionInfo() {}
	CollisionInfo(CollisionDir dir, float depth) : dir(dir), depth(depth) {}
};
/*
	추상 클래스
*/
class Collider : public Component
{
public:
	Collider() = default;
	virtual ~Collider() = default;

protected:
	CollisionType m_CollisionType;		// 컬리전 타입 (노컬리전,블럭, 오버랩)
	D2D1_COLOR_F m_Color;				// 그리기용 색상
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


	// Circle,Box 에서 각자 구현해야한다.
	virtual bool IsCollide(Collider* pOtherComponent) = 0;
};


class IColliderNotify //게임오브젝트가 상속받음
{
public:
	virtual void OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent) = 0;
	virtual void OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) = 0;
	virtual void OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) = 0;
};
