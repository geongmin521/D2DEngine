#include "pch.h"
#include "WinGameApp.h"
#include "D2DRenderer.h"
#include "ResourceManager.h"

#include "TimeSystem.h"
#include "InputSystem.h"
#include "World.h"

WinGameApp::WinGameApp()
{
	m_pResourceManager = new ResourceManager;
}

WinGameApp::~WinGameApp()
{
	if (m_pResourceManager)
	{
		delete m_pResourceManager;
		m_pResourceManager = nullptr;
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_SETFOCUS:
		timeManager->SetTimeScale(1); 
		break;
	case WM_KILLFOCUS:
		timeManager->SetTimeScale(0);
		break;
	case WM_ENTERSIZEMOVE:
		timeManager->SetTimeScale(0);
		break;
	case WM_EXITSIZEMOVE:
		timeManager->InitTime(); //ȣ���� �ѹ����� �ߵ����µ� �׷��� Ż���ϴ°ź��� �׿��ִ� �ð������� �׷��Ű��⵵?
		timeManager->SetTimeScale(1);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


void WinGameApp::Initialize(HINSTANCE hInstance, int nShowCmd)
{
	// �������� ����ϴ� ������ ����,�����κ��� �ۼ��Ѵ�.
	WNDCLASSEXW wcex;
	timeManager->InitTime();
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DEMOGAME));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_DEMOGAME);
	wcex.lpszClassName = L"Test";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	RegisterClassExW(&wcex);
	InitInstance(hInstance, nShowCmd);

	D2DRenderer::GetInstance(m_hWnd); //�̰� ���� �ʹ� ���� �ȵ�ϱ� �����ٶ�
	world = new World;
}

void WinGameApp::Run() 
{
	MSG msg;

	while (true) 
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			//�޼��� �߿� ������ ��Ŀ���� ������ �޼���Ȯ���ϱ�
		}
		else
		{
			timeManager->UpdateTime();
			inputSystem->UpdateKey();
			inputSystem->UpdateMouse(m_hWnd);

			Update(timeManager->GetDeltaTime());
			Render(D2DRenderer::GetInstance()->GetRenderTarget());
			inputSystem->ResetInput();
		}	
	}
	
}

void WinGameApp::Update(float fTimeElapsed)
{
	world->Update(fTimeElapsed);
}

void WinGameApp::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	D2DRenderer::GetInstance()->GetRenderTarget()->BeginDraw();
	D2DRenderer::GetInstance()->GetRenderTarget()->Clear(D2D1::ColorF(D2D1::ColorF::CadetBlue));
	world->Render(pRenderTarget);
	D2DRenderer::GetInstance()->GetRenderTarget()->EndDraw();
}


void WinGameApp::Uninitialize()
{
	D2DRenderer::GetInstance()->Uninitialize(); //�������ϴ°� �����ʳ�?
}

bool WinGameApp::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; 

	RECT rt = { 0, 0, 1920 , 1080 }; //���� ũ���� ������ â ũ�⸦ ���Ѵ�.

	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, 0);

	m_hWnd = CreateWindowW(L"Test", L"test", WS_OVERLAPPEDWINDOW,
		50, 50, rt.right - rt.left, rt.bottom - rt.top, nullptr, nullptr, hInstance, nullptr);

	if (!m_hWnd)
	{
		return FALSE;
	}

	ShowWindow(m_hWnd, nCmdShow);
	UpdateWindow(m_hWnd);

	return TRUE;
}




