#pragma once
class Component;
class World;
class Transform;
class AABB;

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();
	bool isActive;
	std::vector<Component*> m_OwnedComponents;	// ������ ������Ʈ��
	Transform* m_Transform = nullptr;				
	World* owner = nullptr;					// �� ���� ������Ʈ�� ���� ����
	AABB* m_BoundBox;							// �ø��� ���� �ڽ�
	int renderOrder;							//�̰Ŵ� �������� ����ұ�.. �� Ŭ������ ���������?
public:
	virtual void Update(float deltaTime);
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);
	const AABB& GetBoundBox() const { return *m_BoundBox; }
	void SetBoundBox(int x, int y, int weight, int height);
	void AddComponent(Component* pComponent);
	void SetOwner(World* pOwner) { owner = pOwner; } 
	D2D1_VECTOR_2F GetWorldLocation();
	template<typename T>
	T* GetComponent()
	{
		for (int i = 0; i < m_OwnedComponents.size(); i++)
		{
			if (T* component = dynamic_cast<T*>(m_OwnedComponents[i]))
			{
				return component; // ĳ���� ���� �� �ش� ������Ʈ�� ��ȯ
			}
		}
		return nullptr; // ã�� ���� �� nullptr ��ȯ
	}
	// ������Ʈ �� ��Ʋ�� �Լ��� �����մϴ�.
	template<typename T>
	T* CreateComponent()
	{
		bool bIsBase = std::is_base_of<Component, T>::value; // �̰ɷ� ���� Ŭ������ ���Ҽ��ֳ�?
		//assert(bIsBase == true);
		T* pComponent = new T();
		AddComponent(pComponent);
		return pComponent;
	}
};

