#pragma once

#include "../D2DEngine/GameObject.h" //그래 이거 없으면 상속 못받는걸로 알고있는데.. 

//#include "../D2DEngine/AABB.h"

class MapEditer : public GameObject //뭐야 너 상속받는데 어떻게 알고있냐?
{
private:
	bool isActive;
	std::vector<AABB*> mapCollider; //음.. 어떻게 해야하지? 렌더를 들고잇는 모든 오브젝트에 대해 적용되어야할텐데.. 그러면. world가 관리하니까 괜찮을거같고.. 리스트로 관리해서 삽입할까?
	D2D1_VECTOR_2F startPoint;
	D2D1_VECTOR_2F EndPoint;

public:
	MapEditer();
	~MapEditer();
	virtual void Update(float deltaTime);
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);

	bool SaveCollider();
	bool LoadCollider();

};

