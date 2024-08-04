#pragma once

using namespace MathHelper;

class Circle //�������� �浹�� �� �Ǵ��� �׽�Ʈ ���������ϱ� 
{
public:
	Circle() : Center{ 0,0 }, radius(0) {}
public:
	Vector2F Center; 
	float radius;
	
	Circle(const Circle&) = default;
	Circle& operator=(const Circle&) = default;
	Circle(Circle&&) = default;
	Circle& operator=(Circle&&) = default;
	~Circle() = default;

	void SetCenter(float x, float y) { Center = { x, y }; }
	void SetRadius(float _radius) { radius = _radius; } 

	bool CheckIntersect(const Circle& other) const
	{
		Vector2F distance = Center - other.Center;
		
		if (distance.Length() < radius + other.radius) //�߽ɳ����� �Ÿ����� �������� ���� 	ũ�� �浹����
			return false;		
		else
			return true;
	}

	bool CheckPoint(const Vector2F& point) const
	{
		Vector2F distance = Center - point;

		if (distance.Length() < radius ) //�߽ɰ� Ư�� ���� �Ÿ����� �������� ũ�� �浹����
			return false;
		else
			return true;
	}
};

