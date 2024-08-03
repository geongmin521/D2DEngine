#pragma once
#include "Component.h"
//#include "AABB.h"

class Transform;
class AABB;
class RigidBody :
    public Component
{
private:
	bool isGravity;
	float gravityScale;// �߷��� �ٲٰ� �������� �ִµ�..
public:

	RigidBody();
	virtual ~RigidBody();
	virtual void Update(float deltaTime);
	//virtual void Render(ID2D1RenderTarget* pRenderTarget); //�׸��Ŵ� ���� ���µ�.. 
	virtual void Enable() override;
	virtual void Disable() override;

	float getGravity() { return gravityScale; }
	void resetGravity() {  gravityScale = 0; }

};

