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
	CollisionType collisionType;		// �ø��� Ÿ�� (���ø���,��, ������)
	D2D1_COLOR_F color;				// �׸���� ����
	IColliderNotify* notify;
	CollisionLayer layer;
	bool isBlock[2] = { false,false }; //0 x�� 1 y��;
	std::set<Collider*> collideStateCurr;    // ���� �浹 ����
	std::set<Collider*> collideStatePrev;	// ���� �浹 ����
public:

	CollisionType GetCollisionType() { return collisionType; }
	CollisionLayer GetCollisionLayer() { return layer; }
	void SetCollisionType(CollisionType Type) { collisionType = Type; }

	D2D1_COLOR_F GetColor() const { return color; }
	void SetColor(D2D1_COLOR_F val) { color = val; }

	bool IsEmptyCollideStateCurr() { return collideStateCurr.empty(); } //���� �浹�� �ݶ��̴����ִ��� 
	void InsertCollideState(Collider* pColliderComponent) { collideStateCurr.insert(pColliderComponent); }

	void ClearAndBackupCollideState();
	void ProcessOverlap();
	virtual	void ProcessBlock(Collider* otherComponent); //�浹������ ���� �ٸ��� ���Ƽ� ������� ����


	// Circle,Box ���� ���� �����ؾ��Ѵ�. //�ڽ��ݶ��̴��� �̰Ŷ� ������Ʈ�� ��ӹ޾ƾ��ҷ���? ��Ӳ���. 
	virtual bool IsCollide(Collider* otherComponent) = 0;
	virtual bool IsCollide(AABB* aabb) = 0; //�̰Ÿ� �ѳ� ���θ����� �̰Ÿ� ���ø����� ����� �װ��� Ư��ȭ�ϴ°� �?
};

