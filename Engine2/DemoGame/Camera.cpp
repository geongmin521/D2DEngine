#include "../D2DEngine/pch.h"
#include "Camera.h"
#include "..//D2DEngine/CameraScene.h"

Camera::Camera() //ī�޶� �����ҷ��� Ÿ���� ���ؾ��Ѵ�? 
{
	CameraScene* scene = new CameraScene(); //Ÿ���� �����ִ°ɷ� �����ұ�?
	AddComponent(scene);
}

Camera::~Camera()
{
}
