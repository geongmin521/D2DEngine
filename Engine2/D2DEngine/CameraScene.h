#pragma once
//#include "AABB.h"
#include "Component.h" //aabb�����¾ֵ��̸����ٵ� �پ�����.. 

class AABB;
class CameraScene : public Component
{
public:
	CameraScene();
	virtual ~CameraScene();
	virtual void Update(float deltaTime);
	float moveSpeed;
	AABB* viewBoundBox; //AABB�� ��� �ѱ����ٰ� ���Ƴ����ϴµ�.. 

};

