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

bool Map::LoadCollider() //겹치는거같지만 다른점은 그냥편집을 위한 aabb와 boxcollider 생성에 있다. 
{
	std::wifstream file(L"..\\Data\\MapCollider.csv"); //읽기
	if (!file.is_open()) {
		std::cout << "파일을 열 수 없습니다." << std::endl;
		return false;
	}
	std::wstring line;			// 한줄의 문자열	
	boxCols.clear();// 불러올때는 기존의 콜라이더를 지우기
	int colliderCount = 0;			// 콜라이더의 개수
	{
		std::getline(file, line);		// 첫번째 줄 읽기
		std::wstringstream wss(line);
		wss >> colliderCount;
	}
	//m_Animations[index].Frames.reserve(FrameCount);
	for (int j = 0; j < colliderCount; j++)
	{
		AABB* col = new AABB();

		getline(file, line);			// 한줄 읽기
		std::wstringstream wss(line);   // 한줄을 읽어서 wstringstream에 저장
		std::wstring token;
		{
			getline(wss, token, L',');	// wss의 내용을 ,를 기준으로 문자열을 분리
			col->m_Center.x = (float)_wtoi(token.c_str());
			getline(wss, token, L',');
			col->m_Center.y = (float)_wtoi(token.c_str());
			getline(wss, token, L',');
			col->m_Extent.x = (float)_wtoi(token.c_str());
			getline(wss, token, L',');
			col->m_Extent.y = (float)_wtoi(token.c_str());
		}
		boxCols.push_back(new BoxCollider(col)); //오 뭔가 잘되는거같은데?
	}
	return true;
}
