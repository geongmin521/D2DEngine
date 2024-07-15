#include "../D2DEngine/pch.h"			
#include "Map.h"	
#include "../D2DEngine/Bitmap.h"
#include "../D2DEngine/Transform.h"

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
