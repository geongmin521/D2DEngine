#pragma once
#include "IColliderNotify.h"

enum class CollisionType
{
	NoCollision,
	Block,
	Overlap
};

enum class CollisionLayer //레이어로 구분해서 필요한 애들만 충돌검사를 하도록 만들기
{
	Platform,
	Player,
	Web,
	Missile,
	Default
};

/*
	추상 클래스
*/
class AABB;
class Collider
{
public:
	Collider(); //추상클래스라도 생성자는 호출될때니까 여기서 월드한테 등록할수있게하면될듯?
	virtual ~Collider();

protected:
	CollisionType m_CollisionType;		// 컬리전 타입 (노컬리전,블럭, 오버랩)
	D2D1_COLOR_F m_Color;				// 그리기용 색상
	IColliderNotify* notify;
	CollisionLayer layer;
	bool isBlock[2] = { false,false }; //0 x축 1 y축;
	std::set<Collider*> m_CollideStateCurr;    // 현재 충돌 상태
	std::set<Collider*> m_CollideStatePrev;	// 이전 충돌 상태
public:

	CollisionType GetCollisionType() { return m_CollisionType; }
	CollisionLayer GetCollisionLayer() { return layer; }
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
	virtual bool IsCollide(AABB* aabb) = 0; //이거만 한나 새로만들자 이거를 템플릿으로 만들고 그것을 특수화하는건 어떰?
};

