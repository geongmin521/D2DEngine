#include "pch.h"
#include "GameObject.h"
#include "Transform.h"
#include "CameraScene.h" 
#include "D2DRenderer.h"
#include "World.h"
#include "AABB.h"

CameraScene::CameraScene()
{
	moveSpeed = 300;
	viewBoundBox = new AABB();
	viewBoundBox->SetExtent(WinHalfSizeX, WinHalfSizeY);

}

CameraScene::~CameraScene()
{

}

void CameraScene::Update(float deltaTime) //ī�޶�� Ÿ���� Ʈ�������� �ڱ��ó�� ����ϴ°���?
{
	D2D1_MATRIX_3X2_F invserse = owner->transform->worldTransform;  
	D2D1InvertMatrix(&invserse); 
	D2DRenderer::cameraTransform = invserse * D2D1::Matrix3x2F::Translation(WinHalfSizeX, WinHalfSizeY); // ī�޶��� ��ǥ�� ȭ���߾��϶��� 0,0 ���� ���Ǳ�����
	viewBoundBox->SetCenter(owner->transform->worldTransform.dx, owner->transform->worldTransform.dy);
	owner->owner->SetCullingBound(viewBoundBox);
}
//������Ʈ�� �߰��Ҷ� ȭ���߾ӿ� �׸��� �����ϱ�.. 



