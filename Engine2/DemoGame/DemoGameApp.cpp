#include "../D2DEngine/pch.h"

#include "DemoGameApp.h"

#include "../D2DEngine/World.h" //�̷��� 4���� ������ ����? ����� ���� ���̴µ� ��� �ؾ����� ������������..
#include "../D2DEngine/D2DRenderer.h"
#include "../D2DEngine/Transform.h"

#include "MapEditer.h" //��� �ֵ��� ���� ������Ʈ�� ��ӹ޴µ�..  �̰Ŷ����� �׷�������.. 
#include "Map.h"
#include "Character.h"
#include "Camera.h"
//#include "Missile.h"
#include "MissileSpawner.h"
#include "SpiderWeb.h"

void DemoGameApp::Initialize(HINSTANCE hInstance, int nShowCmd)
{
	__super::Initialize(hInstance, nShowCmd);	 // ������ ���� , Direct2D �ʱ�ȭ
	world->CreateGameObject<MapEditer>();
	Map* map = world->CreateGameObject<Map>();
	world->CreateGameObject<Camera>();
	Character* player = world->CreateGameObject<Character>();
	world->CreateGameObject<MissileSpawner>()->target = player->m_Transform;
	SpiderWeb* web = world->CreateGameObject<SpiderWeb>();
	//web->m_Transform->SetParent(player->m_Transform);//�θ����� �Ź����� ���� �پ������� �����ϱ� 
	web->player = player->m_Transform;
	player->web = web;//�����ϰ� ������������ .. 
	//���� ���� �������� �θ�� ������? �׷��� ���ݾ�.. �׸��� �Ź����� ȸ���ϸ� 
	//�����̴����� ���˵��� �׸�����.. 


	//�ڽĿ�����Ʈ�� ���� �����ϴ°� ������?
	//���� �����̶�� ����� ������ ������ �����.. 


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


