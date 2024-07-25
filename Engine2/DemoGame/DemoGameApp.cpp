#include "../D2DEngine/pch.h"

#include "DemoGameApp.h"

#include "../D2DEngine/World.h" 
#include "../D2DEngine/D2DRenderer.h"
#include "../D2DEngine/Transform.h"

#include "MapEditer.h"
#include "Map.h"
#include "Character.h"
#include "Camera.h"
#include "MissileSpawner.h"
#include "SpiderWeb.h"

void DemoGameApp::Initialize(HINSTANCE hInstance, int nShowCmd)
{
	__super::Initialize(hInstance, nShowCmd);	 // 윈도우 생성 , Direct2D 초기화
	world->CreateGameObject<MapEditer>();
	Map* map = world->CreateGameObject<Map>();
	world->CreateGameObject<Camera>();
	Character* player = world->CreateGameObject<Character>();
	world->CreateGameObject<MissileSpawner>()->target = player->m_Transform;
	SpiderWeb* web = world->CreateGameObject<SpiderWeb>();

	web->player = player;
	player->web = web;
} 

void DemoGameApp::Run()
{
	__super::Run();
}

void DemoGameApp::Uninitialize()
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


