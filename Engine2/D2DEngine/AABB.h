#pragma once
#include "Collider.h" //�̷��� �Ȳ��ϱ�? ������.. ������� ��Ŭ���
/*
	AABB (Axis-Aligned Bounding Box) �� ���ĵ� ��� ����

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
	D2D1_VECTOR_2F m_Center; // �߾�
	D2D1_VECTOR_2F m_Extent; // x,y�� Ȯ�尪	
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
		if (BoxA_xmax < BoxB_xmin ||  // �����ʿ� ������ ��ĥ���� ����
			BoxA_xmin > BoxB_xmax ||  // ���ʿ� ������ ��ĥ���� ����
			BoxA_ymax < BoxB_ymin ||  // �Ʒ��� ������ ��ĥ���� ����
			BoxA_ymin > BoxB_ymax)	  // ���� ������ ��ĥ���� ����
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
			other.y > BoxA_ymin && other.y < BoxA_ymax) //���ϳ��� ��簪�� �����̸� �ε���
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void CheckCollisionInfo(const AABB& other, CollisionInfo& info) const //�浹�� ������ ���� ��������
	{
		// self min,max
		D2D1_VECTOR_2F top_right =		{ m_Center.x + m_Extent.x,m_Center.y - m_Extent.y };
		D2D1_VECTOR_2F top_left =		{ m_Center.x - m_Extent.x,m_Center.y - m_Extent.y };
		D2D1_VECTOR_2F bottom_right =	{ m_Center.x + m_Extent.x,m_Center.y + m_Extent.y };
		D2D1_VECTOR_2F bottom_left =	{ m_Center.x - m_Extent.x,m_Center.y + m_Extent.y };

		bool Btop_right = other.CheckPoint(top_right); //�簢���� ���������� �浹ü�� ��� ������ Ȯ���ϰ� �浹�� ����Ȯ��
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
		else  //�����浹�� ���ϸ����ٵ� �̰� ���� �ø��°� ���귮�� �پ���ٵ�.. 
		{
			depth = other.GetMaxY() - GetMinY();
			dir = CollisionDir::Bottom;		
		}
		info.depth = depth;
		info.dir = dir;
	}
};

