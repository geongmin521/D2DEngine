#pragma once

#include "../D2DEngine/GameObject.h" //�׷� �̰� ������ ��� ���޴°ɷ� �˰��ִµ�.. 

//#include "../D2DEngine/AABB.h"

class MapEditer : public GameObject //���� �� ��ӹ޴µ� ��� �˰��ֳ�?
{
private:
	bool isActive;
	std::vector<AABB*> mapCollider; //��.. ��� �ؾ�����? ������ ����մ� ��� ������Ʈ�� ���� ����Ǿ�����ٵ�.. �׷���. world�� �����ϴϱ� �������Ű���.. ����Ʈ�� �����ؼ� �����ұ�?
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

