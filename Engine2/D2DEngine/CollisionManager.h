#pragma once

class Collider;
enum class CollisionLayer;
class CollisionManager
{
private:
	CollisionManager();
	~CollisionManager();
	static CollisionManager* inst;
	std::map<CollisionLayer, std::vector<Collider*>>  colliders;
	std::set<std::pair<CollisionLayer, CollisionLayer>> collisonLayer; //���̾� �� ��鸸 �浹�Ұ���. ��... �̰Ŵ� �����ڿ��� ó������. //�̰͵��� ���ǰ� �ʿ��ϸ� ����� �ʿ��ѵ�.. 
	//�ƴϸ� �̰͵� ���漱�𰡴�?
public:
	static CollisionManager* GetInstance();
	void CollisionCheck();
	void EraseCollider(Collider* col);
	void pushCollider(Collider* col);//�� �̰͵� �ζ��� �ȵ�.. 
};

