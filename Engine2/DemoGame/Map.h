#pragma once
#include "../D2DEngine/GameObject.h"

class BoxCollider;
class Map : public GameObject
{
public:
	Map();
	~Map(); //¿œ¥‹¿∫ 
	bool LoadCollider();
	std::vector<BoxCollider*> boxCols;
};

