#include "../D2DEngine/pch.h"

#include "DemoGameApp.h"

#include "../D2DEngine/World.h" 
#include "../D2DEngine/D2DRenderer.h"
#include "../D2DEngine/Transform.h"


#include "Map.h"

#include "Camera.h"


void DemoGameApp::Initialize(HINSTANCE hInstance, int nShowCmd)
{
	__super::Initialize(hInstance, nShowCmd);	 // ������ ���� , Direct2D �ʱ�ȭ
	//world->CreateGameObject<MapEditer>(); ���丮�� ���Ӱ����Ѱ�? 

} 

void DemoGameApp::Run()
{
	__super::Run();
}

void DemoGameApp::Uninitialize()
{
	__super::Uninitialize();
}

