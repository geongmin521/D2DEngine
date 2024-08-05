#include "pch.h"
#include "Transform.h"

Transform::Transform()
{
	relativeTransform = worldTransform = D2D1::Matrix3x2F::Identity();
}

Transform::~Transform()
{

}

void Transform::Update(float deltaTime) //���� ��� ������Ʈ�� �߽���.. �̹������߾��̾����� ���ڴ� ���̾�.. 
{
	relativeTransform = D2D1::Matrix3x2F::Scale(D2D1::SizeF(relativeScale.x, relativeScale.y)) *
		D2D1::Matrix3x2F::Rotation(relativeRotation, imageCenter) * //�̹����� �߽��� �˾ƾ���.. 
		//�̰� ����.. 
		//�׷��ϱ� ���� ���ϴ°Ŵ� �ϳ��� Ŭ���̾�Ʈ���� �����Ҷ����ϳ��� ��ǥ��� �����ϰ������.. �װ� �̹����� �߽��̰� �׷�����.. ���� Ʈ���������� ó���ؾ��ϴ°� �ƴѰ� ��������.. 
		//�װ� Ȯ���� ������Ʈ���� ������� ���� ����� ��.. 
		//�߽���ǥ�� �����ֵ����غ��ô�. 
		//�ϴ� UI ���� �������? 
		//�� ȸ���� ������Ʈ�� �׳� �߽ɿ� �����־���?

		//�ٵ� �ñ��Ѱ�.. ȸ���� �и� ��ǥ�� ���̷��� ����?? �̰Ŵ� �����.. 
		//������ǥ�� �߽��̶���.. 
		D2D1::Matrix3x2F::Translation(relativeLocation.x, relativeLocation.y);//����Ŀ���.. 
	if (parentScene != nullptr)
		worldTransform = relativeTransform * parentScene->worldTransform;
	else
		worldTransform = relativeTransform;
}


void Transform::SetRelativeRotation(float Rotation)
{
	relativeRotation = Rotation;
	relativeRotation = fmodf(relativeRotation, 360.0f);
}

void Transform::AddRelativeRotation(float Rotation)
{
	relativeRotation += Rotation;
	relativeRotation = fmodf(relativeRotation, 360.0f);
}


void Transform::SetRelativeLocation(const MathHelper::Vector2F& Location) //������ �����ǥ�� �̵���Ű�� ��� ���� ��ǥ�� ����ɼ��ְ��ϱ�
{
	relativeLocation = Location;
	Update(1);
}

void Transform::AddRelativeLocation(float x, float y)
{
	relativeLocation = { relativeLocation.x + x,relativeLocation.y + y };
}

std::wstring Transform::ShowPos()
{
	
	return L"������ǥ: " + std::to_wstring(relativeLocation.x) + L"  " + std::to_wstring(relativeLocation.y)
		+  L"������ǥ: " + std::to_wstring(GetWorldLocation().x) + L"  " + std::to_wstring(GetWorldLocation().y);
}



