#include "../D2DEngine/pch.h"

#include "DemoGameApp.h"

#include "../D2DEngine/World.h" //이렇게 4개를 상위로 뺄까? 헤더가 존나 꼬이는데 어떻게 해야할지 감도안잡히네..
#include "../D2DEngine/D2DRenderer.h"
#include "../D2DEngine/Transform.h"

#include "MapEditer.h" //모든 애들은 게임 오브젝트를 상속받는데..  이거때문에 그런가보네.. 
#include "Map.h"
#include "Character.h"
#include "Camera.h"
//#include "Missile.h"
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
	//web->m_Transform->SetParent(player->m_Transform);//부모관계는 거미줄이 벽에 붙었을때만 세팅하기 
	web->player = player->m_Transform;
	player->web = web;//복잡하게 생각하지말고 .. 
	//벽에 붙은 시점에만 부모로 만들자? 그러면 되잖아.. 그리고 거미줄을 회전하면 
	//스파이더맨이 원궤도를 그리겠지.. 


	//자식오브젝트는 누가 생성하는게 맞을까?
	//만약 본인이라면 월드는 전역적 접근을 줘야함.. 


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


