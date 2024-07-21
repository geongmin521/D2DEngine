#pragma once
#include "MathHelper.h"
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
	AABB() : m_Center{ 0,0 }, m_Extent{ 0,0 } { }
public:
	MathHelper::Vector2F m_Center; // 중앙
	MathHelper::Vector2F m_Extent; // x,y축 확장값	
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

	bool CheckPoint(const MathHelper::Vector2F& other) const
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
};

