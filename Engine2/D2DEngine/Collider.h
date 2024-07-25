#pragma once
#include "IColliderNotify.h"

enum class CollisionType
{
	NoCollision,
	Block,
	Overlap
};

enum class CollisionLayer //���̾�� �����ؼ� �ʿ��� �ֵ鸸 �浹�˻縦 �ϵ��� �����
{
	Platform,
	Player,
	Web,
	Missile,
	Default
};

/*
	�߻� Ŭ����
*/
class AABB;
class Collider
{
public:
	Collider(); //�߻�Ŭ������ �����ڴ� ȣ��ɶ��ϱ� ���⼭ �������� ����Ҽ��ְ��ϸ�ɵ�?
	virtual ~Collider();

protected:
	CollisionType m_CollisionType;		// �ø��� Ÿ�� (���ø���,��, ������)
	D2D1_COLOR_F m_Color;				// �׸���� ����
	IColliderNotify* notify;
	CollisionLayer layer;
	bool isBlock[2] = { false,false }; //0 x�� 1 y��;
	std::set<Collider*> m_CollideStateCurr;    // ���� �浹 ����
	std::set<Collider*> m_CollideStatePrev;	// ���� �浹 ����
public:

	CollisionType GetCollisionType() { return m_CollisionType; }
	CollisionLayer GetCollisionLayer() { return layer; }
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
	virtual bool IsCollide(AABB* aabb) = 0; //�̰Ÿ� �ѳ� ���θ����� �̰Ÿ� ���ø����� ����� �װ��� Ư��ȭ�ϴ°� �?
};

