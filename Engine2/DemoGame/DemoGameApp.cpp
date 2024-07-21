#include "framework.h"
#include "DemoGameApp.h"

#include "../D2DEngine/World.h" //이렇게 4개를 상위로 뺄까? 헤더가 존나 꼬이는데 어떻게 해야할지 감도안잡히네..
#include "../D2DEngine/D2DRenderer.h"

#include "MapEditer.h" //모든 애들은 게임 오브젝트를 상속받는데..  이거때문에 그런가보네.. 
#include "Map.h"
#include "Character.h"
#include "Camera.h"
//#include "Missile.h"
#include "MissileSpawner.h"

void DemoGameApp::Initialize(HINSTANCE hInstance, int nShowCmd)
{
	__super::Initialize(hInstance, nShowCmd);	 // 윈도우 생성 , Direct2D 초기화
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

void DemoGameApp::Uninitialize() //이 하위계층에서는 뭘해야하는거지? 
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


