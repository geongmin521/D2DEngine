#include "../D2DEngine//pch.h"
#include "../D2DEngine/InputSystem.h"
#include "../D2DEngine/D2DRenderer.h"
#include "../D2DEngine/AABB.h"
#include "../D2DEngine/Transform.h"
#include "MapEditer.h"

MapEditer::MapEditer()
{
	renderOrder = 10;
	SetBoundBox(0, 0, 1000, 1000);
}

MapEditer::~MapEditer()
{

}

void MapEditer::Update(float deltaTime)
{

	if (inputSystem->isKeyDown(VK_TAB)) //���� ���콺 ��ǥ�� ���� ��� ��Ʈ �����ϱ�
	{
		isActive = !isActive;
	}
	if (isActive == false)
		return;
    D2D1_VECTOR_2F curPos = { inputSystem->GetMouseState()._x,inputSystem->GetMouseState()._y };
	if (inputSystem->GetMouseButtonDown(0)) //������ ��ǥ����ϰ�
	{
		startPoint = curPos; //ī�޶� �����̴°ɻ���? 
		return;
	}
	if (inputSystem->GetMouseButton(0)) //���������� ���� ��ǥ�� �ڽ� ���
	{
		EndPoint = curPos;
	}
	if (inputSystem->GetMouseButtonUp(0)) //���� ������� ��ǥ�� ���� �ڽ��� ����� ���;ȿ��ֱ�
	{
		AABB* aabb = new AABB(); 
		//�ٵ� �����غ��� �� ���� ��ũ�� ��ǥ�����ٵ�.. ȭ���� �����̸鼭 �ҷ��� ������ǥ�� ������߰ڳ�.. 
		aabb->m_Extent = { abs(startPoint.x - EndPoint.x) / 2, abs(startPoint.y - EndPoint.y) / 2 };
		if (aabb->m_Extent.x < 10 || aabb->m_Extent.y < 10) //�ʹ� �����Ŵ� ���׸�������
			return;
		aabb->m_Center = { startPoint.x + aabb->m_Extent.x, startPoint.y + aabb->m_Extent.y };//���⿡ ������ǥ���ϱ�
		mapCollider.push_back(aabb); //���Ͷ� �ͽ��ٵ� �־��ָ�Ǵµ�
	}

	if (inputSystem->GetMouseButtonDown(2)) //���� ���콺 ��ǥ�� ���� ��� ��Ʈ �����ϱ�
	{
		mapCollider.erase(std::remove_if(mapCollider.begin(),mapCollider.end(), 
			[curPos](const AABB* aabb) { return aabb->CheckPoint(curPos); }),mapCollider.end());
	}

	if (inputSystem->isKeyDown('S'))
	{
		SaveCollider();
		return;
	}
	if (inputSystem->isKeyDown('L'))
	{
		LoadCollider();
		return;
	}
}

void MapEditer::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	pRenderTarget->SetTransform(m_Transform->m_WorldTransform); 
	D2DRenderer::GetInstance()->DrawBox(
		startPoint.x,
		startPoint.y,
		EndPoint.x,
		EndPoint.y);
	for (int i = 0; i < mapCollider.size(); i++)
	{
		D2DRenderer::GetInstance()->DrawBox(
			mapCollider[i]->GetMinX(),
			mapCollider[i]->GetMaxY(),
			mapCollider[i]->GetMaxX(),
			mapCollider[i]->GetMinY());
	}
	pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	if(isActive)
		D2DRenderer::GetInstance()->DrawTextFunc(L" �׸��� ���",0,0);
}

bool MapEditer::SaveCollider()
{
	std::wofstream file(L"..\\Data\\MapCollider.csv"); 
	if (!file.is_open()) {
		std::cout << "������ �� �� �����ϴ�." << std::endl;
		return false; // Return false if file cannot be opened
	}

	int colliderCount = mapCollider.size();

	// Write the collider count as the first line
	file << colliderCount << std::endl;

	// Write each collider's data to subsequent lines
	for (int j = 0; j < colliderCount; j++)
	{
		const AABB* col = mapCollider[j];

		// Write comma-separated values
		file << col->m_Center.x << L',' << col->m_Center.y << L','
			<< col->m_Extent.x << L',' << col->m_Extent.y << std::endl;
	}

	file.close(); // Close the file

	return true;
}

bool MapEditer::LoadCollider() //�̰� �ݺ��Ǵ� ����ε� �ܺ� ���� �о���� ������ �ϳ��� �����Ҽ��ִ� �ý����� ��������
{
	std::wifstream file(L"..\\Data\\MapCollider.csv"); //�б�
	if (!file.is_open()) {
		std::cout << "������ �� �� �����ϴ�." << std::endl;
		return false;
	}
	std::wstring line;			// ������ ���ڿ�	
	mapCollider.clear();// �ҷ��ö��� ������ �ݶ��̴��� �����
	int colliderCount = 0;			// �ݶ��̴��� ����
	{
		std::getline(file, line);		// ù��° �� �б�
		std::wstringstream wss(line);
		wss >> colliderCount;
	}

	for (int j = 0; j < colliderCount; j++)
	{
		AABB* col = new AABB();

		getline(file, line);			// ���� �б�
		std::wstringstream wss(line);   // ������ �о wstringstream�� ����
		std::wstring token;
		{
			getline(wss, token, L',');	// wss�� ������ ,�� �������� ���ڿ��� �и�
			col->m_Center.x = (float)_wtoi(token.c_str());
			getline(wss, token, L',');
			col->m_Center.y = (float)_wtoi(token.c_str());
			getline(wss, token, L',');
			col->m_Extent.x = (float)_wtoi(token.c_str());
			getline(wss, token, L',');
			col->m_Extent.y = (float)_wtoi(token.c_str());
		}
		mapCollider.push_back(col); //�� ���� �ߵǴ°Ű�����?
	}
	return true;
}
