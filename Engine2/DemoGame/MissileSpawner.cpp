#include "../D2DEngine/pch.h"
#include "../D2DEngine/Transform.h"
#include "MissileSpawner.h"
#include "Missile.h"
#include "../D2DEngine/World.h"


MissileSpawner::MissileSpawner()
{
	spwanTimer = 3;
}

MissileSpawner::~MissileSpawner()
{
}

void MissileSpawner::CreateMissile()
{
	Missile* newMissile = new Missile();

	std::random_device rd;  
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> X(0, WinSizeX);
	std::uniform_int_distribution<> Y(0, WinSizeY);
	//
	newMissile->m_Transform->SetRelativeLocation({ (float)X(gen), (float)Y(gen) });
	newMissile->m_pOwner = this->m_pOwner;

	newMissile->target = target;
	m_pOwner->m_GameObjects.push_back(newMissile);
}

void MissileSpawner::Update(float deltaTime)
{
	Timer -= deltaTime;
	if (Timer < 0)
	{
		Timer = spwanTimer;
		CreateMissile();
	}
}

void MissileSpawner::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
}

