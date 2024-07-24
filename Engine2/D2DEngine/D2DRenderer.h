#pragma once
//#include <d2d1.h>
class AABB;
class D2DRenderer 
{
public:
	D2DRenderer();
	~D2DRenderer();

	static D2D1_MATRIX_3X2_F m_CameraTransform;

	static D2DRenderer* GetInstance(HWND hWnd = nullptr);
	void Initialize(HWND hWnd);
	void Uninitialize();
	
	ID2D1Factory* GetFactory() { return m_pD2DFactory; }
	ID2D1HwndRenderTarget* GetRenderTarget() { return m_pRenderTarget; }
	size_t GetUsedVRAM();
	void DrawTextFunc(std::wstring text,int x, int y);
	void DrawBox(int left, int top, int right, int bottom);
	void DrawAABB(AABB aabb);
	void DrawLine(MathHelper::Vector2F start, MathHelper::Vector2F end);
public:
	 //왜 못찾지? //이거 스태틱안되나본데?
	ID2D1Factory* m_pD2DFactory;			// D2D 개체 인터페이스 포인터 변수
	ID2D1HwndRenderTarget* m_pRenderTarget; //그리는 렌더타겟								//이미지 생성에필요
	IWICImagingFactory* m_pWICFactory;		// D2D비트맵 생성을 위한 이미지 처리 인터페이스 //이미지 생성에필요 
	ID2D1SolidColorBrush* g_pBlackBrush;	//뭔가를 그리기위한 객체
	IDWriteFactory* m_pDWriteFactory;		// TextFormat생성을 위한 팩토리
	IDWriteTextFormat* m_pDWriteTextFormat; // 기본 텍스트 출력을 위한 Format
	ID2D1SolidColorBrush* m_pBrush;			// 렌더타겟이 생성하는 리소스 역시 장치의존

	IDXGIFactory4* m_pDXGIFactory;			// DXGI팩토리 
	IDXGIAdapter3* m_pDXGIAdapter;			// 비디오카드 정보에 접근 가능한 인터페이스 
	HWND m_hWnd;							// 렌더타겟을 생성할 윈도우 핸들
	D2D_SIZE_U	m_ClientSize;				// 렌더타겟의 크기

private:
	static D2DRenderer* inst;
};




