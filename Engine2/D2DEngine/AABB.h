#pragma once
#include "Collider.h" //이러면 안꼬일까? 무섭네.. 헤더파일 인클루드
/*
	AABB (Axis-Aligned Bounding Box) 축 정렬된 경계 상자

	  +y
	  ^
	  |         +----------------------max
	  |         |                      |
	  |         |		 center        |
	  |	        |          +---------- |
	  |         |          |  extend.x |
	  |         |  extend.y|           |
	  |         min--------------------+
	--+------------------------------------> +x
   0,0
*/
class AABB
{
public:
	AABB() : m_Center{ 0 }, m_Extent{ 0 } { }
public:
	D2D1_VECTOR_2F m_Center; // 중앙
	D2D1_VECTOR_2F m_Extent; // x,y축 확장값	
	// minX = m_Center.x - m_Extent.x
	// maxX = m_Center.x + m_Extent.x
	// minY = m_Center.y - m_Extent.y
	// maxY = m_Center.y + m_Extent.y

	AABB(const AABB&) = default;
	AABB& operator=(const AABB&) = default;
	AABB(AABB&&) = default;
	AABB& operator=(AABB&&) = default;
	~AABB() = default;

	void SetCenter(float x, float y) { m_Center = { x, y }; }
	void SetExtent(float x, float y) { m_Extent = { x, y }; }
	float GetMinX() const { return m_Center.x - m_Extent.x; }
	float GetMaxX() const { return m_Center.x + m_Extent.x; }
	float GetMinY() const { return m_Center.y - m_Extent.y; }
	float GetMaxY() const { return m_Center.y + m_Extent.y; }

	bool CheckIntersect(const AABB& other) const
	{
		// self min,max
		float BoxA_xmin = m_Center.x - m_Extent.x;
		float BoxA_xmax = m_Center.x + m_Extent.x;
		float BoxA_ymin = m_Center.y - m_Extent.y;
		float BoxA_ymax = m_Center.y + m_Extent.y;

		// other min,max
		float BoxB_xmin = other.m_Center.x - other.m_Extent.x;
		float BoxB_xmax = other.m_Center.x + other.m_Extent.x;
		float BoxB_ymin = other.m_Center.y - other.m_Extent.y;
		float BoxB_ymax = other.m_Center.y + other.m_Extent.y;

		// Check for no overlap conditions
		if (BoxA_xmax < BoxB_xmin ||  // 오른쪽에 있으면 겹칠수가 없음
			BoxA_xmin > BoxB_xmax ||  // 왼쪽에 있으면 겹칠수가 없음
			BoxA_ymax < BoxB_ymin ||  // 아래에 있으면 겹칠수가 없음
			BoxA_ymin > BoxB_ymax)	  // 위에 있으면 겹칠수가 없음
		{
			return false;
		}

		return true;

	}

	bool CheckPoint(const D2D1_VECTOR_2F& other) const
	{
		// self min,max
		float BoxA_xmin = m_Center.x - m_Extent.x;
		float BoxA_xmax = m_Center.x + m_Extent.x;
		float BoxA_ymin = m_Center.y - m_Extent.y;
		float BoxA_ymax = m_Center.y + m_Extent.y;
		if (other.x > BoxA_xmin && other.x < BoxA_xmax &&
			other.y > BoxA_ymin && other.y < BoxA_ymax) //점하나가 모든값의 안쪽이면 부딪힘
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void CheckCollisionInfo(const AABB& other, CollisionInfo& info) const //충돌을 감지한 변을 가져오기
	{
		// self min,max
		D2D1_VECTOR_2F top_right =		{ m_Center.x + m_Extent.x,m_Center.y - m_Extent.y };
		D2D1_VECTOR_2F top_left =		{ m_Center.x - m_Extent.x,m_Center.y - m_Extent.y };
		D2D1_VECTOR_2F bottom_right =	{ m_Center.x + m_Extent.x,m_Center.y + m_Extent.y };
		D2D1_VECTOR_2F bottom_left =	{ m_Center.x - m_Extent.x,m_Center.y + m_Extent.y };

		bool Btop_right = other.CheckPoint(top_right); //사각형의 각꼭짓점이 충돌체의 어디에 들어가는지 확인하고 충돌한 방향확인
		bool Btop_left = other.CheckPoint(top_left);
		bool Bbottom_right = other.CheckPoint(bottom_right);
		bool Bbottom_left = other.CheckPoint(bottom_left);

		float depth;
		CollisionDir dir;
		if (Btop_right && Btop_left)
		{
			depth = other.GetMinY() - GetMaxY();
			dir = CollisionDir::Top;
		}
		else if (Btop_right && Bbottom_right)
		{
			depth = other.GetMaxX() - GetMinX();
			dir = CollisionDir::Right;
		}
		else if (Bbottom_left && Btop_left)
		{
			depth = other.GetMinX() - GetMaxX();
			dir = CollisionDir::Left;
		}
		else  //바텀충돌이 제일많을텐데 이걸 위로 올리는게 연산량이 줄어들텐데.. 
		{
			depth = other.GetMaxY() - GetMinY();
			dir = CollisionDir::Bottom;		
		}
		info.depth = depth;
		info.dir = dir;
	}
};

