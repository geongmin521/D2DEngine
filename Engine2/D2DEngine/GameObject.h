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
	std::vector<Component*> m_OwnedComponents;	// 소유한 컴포넌트들
	Transform* m_Transform = nullptr;				
	World* m_pOwner = nullptr;					// 이 게임 오브젝트가 속한 월드
	AABB* m_BoundBox;							// 컬링을 위한 박스
	int renderOrder;							//이거는 누가한테 줘야할까.. 각 클래스가 들고있을까?
public:
	virtual void Update(float deltaTime);
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);
	const AABB& GetBoundBox() const { return *m_BoundBox; }
	void SetBoundBox(int x, int y, int weight, int height);
	void AddComponent(Component* pComponent);
	void SetOwner(World* pOwner) { m_pOwner = pOwner; } 
	D2D1_VECTOR_2F GetWorldLocation();
	template<typename T>
	T* GetComponent()
	{
		for (int i = 0; i < m_OwnedComponents.size(); i++)
		{
			if (T* component = dynamic_cast<T*>(m_OwnedComponents[i]))
			{
				return component; // 캐스팅 성공 시 해당 컴포넌트를 반환
			}
		}
		return nullptr; // 찾기 실패 시 nullptr 반환
	}
	// 컴포넌트 를 템틀릿 함수로 생성합니다.
	template<typename T>
	T* CreateComponent()
	{
		bool bIsBase = std::is_base_of<Component, T>::value; // 이걸로 원본 클래스를 구할수있나?
		//assert(bIsBase == true);
		T* pComponent = new T();
		AddComponent(pComponent);
		return pComponent;
	}
};

