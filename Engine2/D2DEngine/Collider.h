#pragma once
#include "IColliderNotify.h"

enum class CollisionType
{
	NoCollision,
	Block,
	Overlap
};

/*
	�߻� Ŭ����
*/
class Collider
{
public:
	Collider() = default;
	virtual ~Collider() = default;

protected:
	CollisionType m_CollisionType;		// �ø��� Ÿ�� (���ø���,��, ������)
	D2D1_COLOR_F m_Color;				// �׸���� ����
	IColliderNotify* notify;
	std::set<Collider*> m_CollideStateCurr;    // ���� �浹 ����
	std::set<Collider*> m_CollideStatePrev;	// ���� �浹 ����
public:

	CollisionType GetCollisionType() { return m_CollisionType; }
	void SetCollisionType(CollisionType Type) { m_CollisionType = Type; }

	D2D1_COLOR_F GetColor() const { return m_Color; }
	void SetColor(D2D1_COLOR_F val) { m_Color = val; }

	bool IsEmptyCollideStateCurr() { return m_CollideStateCurr.empty(); } //���� �浹�� �ݶ��̴����ִ��� 
	void InsertCollideState(Collider* pColliderComponent) { m_CollideStateCurr.insert(pColliderComponent); }

	void ClearAndBackupCollideState();
	void ProcessOverlap();
	virtual	void ProcessBlock(Collider* pOtherComponent); //�浹������ ���� �ٸ��� ���Ƽ� ������� ����


	// Circle,Box ���� ���� �����ؾ��Ѵ�. //�ڽ��ݶ��̴��� �̰Ŷ� ������Ʈ�� ��ӹ޾ƾ��ҷ���? ��Ӳ���. 
	virtual bool IsCollide(Collider* pOtherComponent) = 0;
};

