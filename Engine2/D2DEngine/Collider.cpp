#include "pch.h"
#include "MathHelper.h"
#include "Collider.h"
#include "GameObject.h"
#include "Movement.h"
#include "BoxCollider.h"
#include "../DemoGame/Character.h"

void Collider::ClearAndBackupCollideState()
{
}

void Collider::ProcessOverlap()
{
}

void Collider::ProcessBlock(Collider* pOtherComponent)
{
	notify->OnBlock(this, pOtherComponent);
	//Ÿ�������� �ٿ�ĳ������ �浹�Ǿ��ٴ°��� �����ֱ�.. 
	//(Character*)(((BoxCollider*)pOtherComponent)->m_pOwner).;
}
