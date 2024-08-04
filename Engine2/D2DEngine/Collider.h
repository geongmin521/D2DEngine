#pragma once
#include "IColliderNotify.h"

enum class CollisionType //�浹 Ÿ��
{
	NoCollision,
	Block,
	Overlap
};

enum class ColliderType //�浹ü�� Ÿ��
{
	Box,
	Circle
};

enum class CollisionLayer //���̾�� �����ؼ� �ʿ��� �ֵ鸸 �浹�˻縦 �ϵ��� �����
{
	Tower, 
	Enemy,
	Bullet,
	Default //����Ʈ�� �������� �浹����? �ƴϸ� ��ζ� �浹�ؾ��ϳ�? 
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
	ColliderType colliderType;		// �ݶ��̴� ���
	D2D1_COLOR_F color;				// �׸���� ����
	IColliderNotify* notify;
	CollisionLayer layer;
	bool isBlock[2] = { false,false }; //0 x�� 1 y��;
	std::set<Collider*> collideStateCurr;    // ���� �浹 ����
	std::set<Collider*> collideStatePrev;	 // ���� �浹 ����
public:

	CollisionType GetCollisionType() { return collisionType; }
	ColliderType GetColliderType() { return colliderType; }
	CollisionLayer GetCollisionLayer() { return layer; }
	void SetCollisionType(CollisionType Type) { collisionType = Type; }

	D2D1_COLOR_F GetColor() const { return color; }
	void SetColor(D2D1_COLOR_F val) { color = val; }

	bool IsEmptyCollideStateCurr() { return collideStateCurr.empty(); } //���� �浹�� �ݶ��̴����ִ��� 
	void InsertCollideState(Collider* pColliderComponent) { collideStateCurr.insert(pColliderComponent); }//set�̶� ��ġ�°� �����Ű�.. 
	//�浹�� �ݶ��̴� ��Ͽ������� �־���.. 

	void ClearAndBackupCollideState();	//����� ������ ���ؼ� �� �ݶ��̴����� �´½�ȣ�� ���������. 
	void ProcessOverlap();				//��ġ���߿� notify���� �˷�����ϰ�..  ��״� �� virtual�� �ƴ���?
	virtual	void ProcessBlock(Collider* ownedComponent, Collider* otherComponent); 
	virtual bool IsCollide(Collider* ownedComponent) = 0;
};

