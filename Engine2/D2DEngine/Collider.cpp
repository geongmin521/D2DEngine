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
	//타입을보고 다운캐스팅후 충돌되었다는것을 보내주기.. 
	//(Character*)(((BoxCollider*)pOtherComponent)->m_pOwner).;
}
