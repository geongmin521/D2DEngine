#include "pch.h"
#include "Collider.h"
#include "CollisionManager.h"

Collider::Collider()
{
	CollisionManager::GetInstance()->pushCollider(this);
}

Collider::~Collider()
{
	CollisionManager::GetInstance()->EraseCollider(this);
}

void Collider::ClearAndBackupCollideState()
{
    //�ߺ����¿� ���� ó���� ���ϰ� ����.. �ٲ��ֱ�...
    collideStatePrev = collideStateCurr; //����� ������ �ǰ� 
    collideStateCurr.clear(); //����� ���������

    //�̷��� �ݶ��̴��� ��ø�� ���� ó���� ��� ��������? 
}

void Collider::ProcessOverlap()
{
    //�浹�� ���� ����
    for (auto* collider : collideStateCurr) {
        if (collideStatePrev.find(collider) == collideStatePrev.end()) {
            notify->OnBeginOverlap(this, collider);
        }
    }

    // �浹�� ���� ����
    for (auto* collider : collideStatePrev) {
        if (collideStateCurr.find(collider) == collideStateCurr.end()) {
            notify->OnEndOverlap(this, collider);
        }
    }
    for (auto* collider : collideStateCurr) {
        notify->OnStayOverlap(this, collider);
    }
    ClearAndBackupCollideState();
}

void Collider::ProcessBlock(Collider* ownedComponent, Collider* otherComponent)
{
	notify->OnBlock(ownedComponent, otherComponent);
}
