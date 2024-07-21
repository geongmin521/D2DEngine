#include "framework.h"
#include "DemoGameApp.h"

#include "../D2DEngine/World.h" //�̷��� 4���� ������ ����? ����� ���� ���̴µ� ��� �ؾ����� ������������..
#include "../D2DEngine/D2DRenderer.h"

#include "MapEditer.h" //��� �ֵ��� ���� ������Ʈ�� ��ӹ޴µ�..  �̰Ŷ����� �׷�������.. 
#include "Map.h"
#include "Character.h"
#include "Camera.h"
//#include "Missile.h"
#include "MissileSpawner.h"

void DemoGameApp::Initialize(HINSTANCE hInstance, int nShowCmd)
{
	__super::Initialize(hInstance, nShowCmd);	 // ������ ���� , Direct2D �ʱ�ȭ
	world->CreateGameObject<MapEditer>();
	Map* map = world->CreateGameObject<Map>();
	for (int i = 0; i < map->boxCols.size(); i++)
	{
		world->m_Colliders.push_back(map->boxCols[i]);
	}
	
	world->CreateGameObject<Camera>();
	world->CreateGameObject<MissileSpawner>()->target =
	world->CreateGameObject<Character>()->m_Transform;
} 

void DemoGameApp::Run()
{
	__super::Run();
}

void DemoGameApp::Uninitialize() //�� �������������� ���ؾ��ϴ°���? 
{
	__super::Uninitialize();
}

//void DemoGameApp::Update(float fTimeElapsed)
//{
//	__super::Update(fTimeElapsed);
//}
//
//void DemoGameApp::Render(ID2D1HwndRenderTarget* pRenderTarget)
//{
//	__super::Render(pRenderTarget);
//}


