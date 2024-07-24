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
	 //�� ��ã��? //�̰� ����ƽ�ȵǳ�����?
	ID2D1Factory* m_pD2DFactory;			// D2D ��ü �������̽� ������ ����
	ID2D1HwndRenderTarget* m_pRenderTarget; //�׸��� ����Ÿ��								//�̹��� �������ʿ�
	IWICImagingFactory* m_pWICFactory;		// D2D��Ʈ�� ������ ���� �̹��� ó�� �������̽� //�̹��� �������ʿ� 
	ID2D1SolidColorBrush* g_pBlackBrush;	//������ �׸������� ��ü
	IDWriteFactory* m_pDWriteFactory;		// TextFormat������ ���� ���丮
	IDWriteTextFormat* m_pDWriteTextFormat; // �⺻ �ؽ�Ʈ ����� ���� Format
	ID2D1SolidColorBrush* m_pBrush;			// ����Ÿ���� �����ϴ� ���ҽ� ���� ��ġ����

	IDXGIFactory4* m_pDXGIFactory;			// DXGI���丮 
	IDXGIAdapter3* m_pDXGIAdapter;			// ����ī�� ������ ���� ������ �������̽� 
	HWND m_hWnd;							// ����Ÿ���� ������ ������ �ڵ�
	D2D_SIZE_U	m_ClientSize;				// ����Ÿ���� ũ��

private:
	static D2DRenderer* inst;
};




