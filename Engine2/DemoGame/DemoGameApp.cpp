#include "../D2DEngine/pch.h"

#include "DemoGameApp.h"

#include "../D2DEngine/World.h" 
#include "../D2DEngine/D2DRenderer.h"
#include "../D2DEngine/Transform.h"


#include "Map.h"

#include "Camera.h"


void DemoGameApp::Initialize(HINSTANCE hInstance, int nShowCmd)
{
	__super::Initialize(hInstance, nShowCmd);	 // 윈도우 생성 , Direct2D 초기화
	//world->CreateGameObject<MapEditer>(); 팩토리에 위임가능한가? 

} 

void DemoGameApp::Run()
{
	__super::Run();
}

void DemoGameApp::Uninitialize()
{
	__super::Uninitialize();
}

