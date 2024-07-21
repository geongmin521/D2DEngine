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
	//���Ի����� ���� �Ͼ�Ű����ϱ�.. ����Ʈ�ΰ�..
	// ��ȸ�� ���̵��µ� �����ΰ�.. 
};

