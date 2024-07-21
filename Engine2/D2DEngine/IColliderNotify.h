#pragma once

class Collider;
class IColliderNotify 
{
public:
	virtual void OnBlock		(Collider* pOtherComponent) = 0;
	virtual void OnBeginOverlap (Collider* pOtherComponent) = 0;
	virtual void OnEndOverlap	(Collider* pOtherComponent) = 0;
};
