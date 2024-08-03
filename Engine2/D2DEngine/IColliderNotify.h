#pragma once

class Collider;
class IColliderNotify 
{
public:
	virtual void OnBlock		(Collider* otherComponent) = 0;
	virtual void OnBeginOverlap (Collider* otherComponent) = 0;
	virtual void OnEndOverlap	(Collider* otherComponent) = 0;
};
