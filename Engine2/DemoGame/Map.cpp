#include "../D2DEngine/pch.h"			
#include "../D2DEngine/Bitmap.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/AABB.h"
#include "../D2DEngine/BoxCollider.h"

#include "Map.h"	

Map::Map()
{
	renderOrder = -100;
	AddComponent(new Bitmap(L"..\\Data\\map.png"));
	D2D1_SIZE_F size = GetComponent<Bitmap>()->m_pBitmap->GetSize();
	SetBoundBox(0, 0, size.width, size.height);
	m_Transform->m_RelativeScale = { 3,2.4 };
}

Map::~Map()
{
}

bool Map::LoadCollider() //��ġ�°Ű����� �ٸ����� �׳������� ���� aabb�� boxcollider ������ �ִ�. 
{
	std::wifstream file(L"..\\Data\\MapCollider.csv"); //�б�
	if (!file.is_open()) {
		std::cout << "������ �� �� �����ϴ�." << std::endl;
		return false;
	}
	std::wstring line;			// ������ ���ڿ�	
	boxCols.clear();// �ҷ��ö��� ������ �ݶ��̴��� �����
	int colliderCount = 0;			// �ݶ��̴��� ����
	{
		std::getline(file, line);		// ù��° �� �б�
		std::wstringstream wss(line);
		wss >> colliderCount;
	}
	//m_Animations[index].Frames.reserve(FrameCount);
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
		boxCols.push_back(new BoxCollider(col)); //�� ���� �ߵǴ°Ű�����?
	}
	return true;
}