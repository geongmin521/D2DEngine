#include "../D2DEngine/pch.h"
#include "../D2DEngine/Transform.h"
#include "MissileSpawner.h"
#include "Missile.h"


MissileSpawner::MissileSpawner()
{
	spwanTimer = 1;
}

MissileSpawner::~MissileSpawner()
{
}

void MissileSpawner::CreateMissile()
{
	Missile* newMissile = new Missile();

	std::random_device rd;  
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> X(0, WinSizeX); //이거는 쓸때마다 만들어야하나? 유틸리티로 빼놓을까? 
	std::uniform_int_distribution<> Y(0, WinSizeY);

	newMissile->m_Transform->SetRelativeLocation({ (float)X(gen), (float)Y(gen) });
	newMissile->target = target;//각자한테 타겟을 넣어줘야하나? 미사일은 원콜라이더로 충돌시 그 객체를 타겟으로 넣는식으로 업그레이드하자ㅏ.. 
	missiles.push_back(newMissile);
}

void MissileSpawner::Update(float deltaTime)
{
	Timer -= deltaTime;
	if (Timer < 0)
	{
		Timer = spwanTimer;
		CreateMissile();
	}

	for (auto e : missiles)
	{
		e->Update(deltaTime);
	}
}

void MissileSpawner::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	for (auto e : missiles)
	{
		e->Render(pRenderTarget);
	}
}

