#pragma once

class Collider;
class CollisionManager
{
private:
	CollisionManager();
	~CollisionManager();
	static CollisionManager* inst;
	std::vector<Collider*> m_Colliders;
public:
	static CollisionManager* GetInstance();
	void CollisionCheck();
	void pushCollider(Collider* col) { m_Colliders.push_back(col); }
};

