#pragma once
//#include <d2d1.h>
class AABB;
class Circle;
class D2DRenderer 
{
public:
	D2DRenderer();
	~D2DRenderer();

	static D2D1_MATRIX_3X2_F cameraTransform;

	static D2DRenderer* GetInstance(HWND hWnd = nullptr);
	void Initialize(HWND hWnd);
	void Uninitialize();
	
	ID2D1Factory* GetFactory() { return D2DFactory; }
	ID2D1HwndRenderTarget* GetRenderTarget() { return RenderTarget; }
	size_t GetUsedVRAM();
	void DrawTextFunc(std::wstring text,int x, int y);
	void DrawBox(int left, int top, int right, int bottom);
	void DrawAABB(AABB& aabb);
	void DrawLine(MathHelper::Vector2F start, MathHelper::Vector2F end);
	void DrawCircle(Circle& circle);
public:
	ID2D1Factory* D2DFactory;			// D2D ��ü �������̽� ������ ����
	ID2D1HwndRenderTarget* RenderTarget; //�׸��� ����Ÿ��								//�̹��� �������ʿ�
	IWICImagingFactory* WICFactory;		// D2D��Ʈ�� ������ ���� �̹��� ó�� �������̽� //�̹��� �������ʿ� 
	ID2D1SolidColorBrush* greenBrush;	//������ �׸������� ��ü
	IDWriteFactory* DWriteFactory;		// TextFormat������ ���� ���丮
	IDWriteTextFormat* DWriteTextFormat; // �⺻ �ؽ�Ʈ ����� ���� Format
	ID2D1SolidColorBrush* Brush;			// ����Ÿ���� �����ϴ� ���ҽ� ���� ��ġ����

	IDXGIFactory4* DXGIFactory;			// DXGI���丮 
	IDXGIAdapter3* DXGIAdapter;			// ����ī�� ������ ���� ������ �������̽� 
	HWND hWnd;							// ����Ÿ���� ������ ������ �ڵ�
	D2D_SIZE_U	ClientSize;				// ����Ÿ���� ũ��

private:
	static D2DRenderer* inst;
};




