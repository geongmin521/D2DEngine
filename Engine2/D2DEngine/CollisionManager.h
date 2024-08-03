#pragma once

class Collider;
class CollisionManager
{
private:
	CollisionManager();
	~CollisionManager();
	static CollisionManager* inst;
	std::vector<Collider*> colliders;
public:
	static CollisionManager* GetInstance();
	void CollisionCheck();
	void EraseCollider(Collider* col);
	void pushCollider(Collider* col) { colliders.push_back(col); }
};

