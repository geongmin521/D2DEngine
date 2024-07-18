#pragma once
#include "Component.h"
#include "MathHelper.h"

class Transform;

class Movement :
    public Component
{
public:
	Movement(Transform* target, float Speed); //�̰Ŵ� �����ڿ��� �־������. 
	virtual ~Movement() = default;
	
protected:
	float			m_Speed = 0.0f;		// 1�ʴ� �̵��� �ӷ�
	
	MathHelper::Vector2F	m_Direction{ 0.0f,0.0f };	// ���� ���ֺ���
	MathHelper::Vector2F	m_Velocity;		// �ӵ� ����
	Transform* transform; // ��ġ�� ������ ������Ʈ
	D2D_VECTOR_2F 		m_PrevRelativeLocation = { 0,0 }; // ��� ��ġ
	//D2D_VECTOR_2F 		m_RelativeLocation = { 0,0 }; // ��� ��ġ ������ġ�� �����°ǰ�? 
	//�ƴ��� ���⸸ 0���� ��������.. ������ ��ü���������� ���������� Ŀ���ٴ°ǵ�.. �ϴ� �غ��� �ٲ㺼��? 
	//���� ��Ȯ�ѰŴ� �������� �� ���̸� �ľ��ؼ� �׸�ŭ �÷��ִ°� ���� ��Ȯ���� �ӵ��� ���⵵ �ȹް�.. 
public:
	virtual void Update(float deltaTime);
	bool			isBlock[4] = { false,false,false,false };//��, �Ʒ�, ����, ������ // �ݶ��̴��� ���� ������ Ȱ��ȭ
	void SetSceneComponent(Transform* val) { transform = val; }
	void SetSpeed(float speed) { m_Speed = speed; };
	float GetSpeed() { return m_Speed; };
	void PrevPosition();
	virtual void SetDirection(const MathHelper::Vector2F& Direction);
	const MathHelper::Vector2F& GetDirection() { return m_Direction; };
};

