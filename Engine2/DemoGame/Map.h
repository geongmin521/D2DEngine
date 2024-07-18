#pragma once
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/IColliderNotify.h"

class Collider;
class Map : public GameObject , public IColliderNotify
{
public:
	Map();
	~Map(); //¿œ¥‹¿∫ 
	bool LoadCollider();
	virtual void OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent) override;
	virtual void OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;
	virtual void OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;
	std::vector<Collider*> boxCols;
};

