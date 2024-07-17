#pragma once
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
	void ProcessBlock(Collider* pOtherComponent);


	// Circle,Box ���� ���� �����ؾ��Ѵ�.
	virtual bool IsCollide(Collider* pOtherComponent) = 0;
};


class IColliderNotify //���ӿ�����Ʈ�� ��ӹ���
{
public:
	virtual void OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent) = 0;
	virtual void OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) = 0;
	virtual void OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) = 0;
};
