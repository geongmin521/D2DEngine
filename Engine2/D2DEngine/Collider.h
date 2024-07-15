#pragma once
#include "Component.h"

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
{//아 아니다 매니저가 매니저는 따로 있을거같고.. 콜라이더도 겹치고있는 콜라이더와 아닌 콜라이더로 나뉠거같고.. 
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
	//충돌했을때 새로 넣으면되고

	//빠지는거는 언제냐.. 리스트에있는 애들이랑은 매초 검사를 하다가. 더이상 안하게 되면 빠지면되고
	//넣는거는 언제 넣어줘야하냐.. 만약한다고 모든 콜라이더와 검사를 해야하는거지?
	
	//일단 매프레임 하는게 제일 편하긴한데.. 움직이지 않는것들도 많으니까 내 생각에는 매프레임하지말고
	//움직임이 있는 애들만 본인을 제외한 나머지들에 대해서 검사할려고했었는데.. 

	//교수님 준거는 보니가 매프레임 모든 오브젝트들과 충돌처리를 하고.. 이전과 이후를 비교해서 충돌 상태에 따라 상태변화를 보내주는듯.. 
	//그러면 모든 콜라이더를 들고있는 매니저는 있어야겠지.. 

	void ClearAndBackupCollideState(); //이거는 뭐하는 애들이지?
	void ProcessOverlap();
	void ProcessBlock(Collider* pOtherComponent);


	// Circle,Box 에서 각자 구현해야한다.
	virtual bool IsCollide(Collider* pOtherComponent) = 0;
};

class ColliderComponent;
class IColliderNotify //이 인터페이스는 하위 콜라이더에게도 상속받아야하는거지?
{
public:
	virtual void OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent) = 0;
	virtual void OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) = 0;
	virtual void OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) = 0;
};
