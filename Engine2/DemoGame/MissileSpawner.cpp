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
	std::uniform_int_distribution<> X(0, WinSizeX); //�̰Ŵ� �������� �������ϳ�? ��ƿ��Ƽ�� ��������? 
	std::uniform_int_distribution<> Y(0, WinSizeY);

	newMissile->m_Transform->SetRelativeLocation({ (float)X(gen), (float)Y(gen) });
	newMissile->target = target;//�������� Ÿ���� �־�����ϳ�? �̻����� ���ݶ��̴��� �浹�� �� ��ü�� Ÿ������ �ִ½����� ���׷��̵����ڤ�.. 
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

