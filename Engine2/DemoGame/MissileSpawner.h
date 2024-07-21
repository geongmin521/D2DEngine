#pragma once
#include "../D2DEngine//GameObject.h"

class Missile;
class MissileSpawner : public GameObject
{
private:
	float Timer;
	float spwanTimer;
	std::list<Missile*> missiles;
	
public:
	Transform* target;
	MissileSpawner();
	~MissileSpawner();
	void CreateMissile();
	virtual void Update(float deltaTime) override;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget) override;
	//삽입삭제가 많이 일어날거같으니까.. 리스트인가..
	// 순회도 많이도는데 벡터인가.. 
};

