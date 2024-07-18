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
	m_ViewBoundBox = new AABB();
	m_ViewBoundBox->SetExtent(WinHalfSizeX, WinHalfSizeY);
}

CameraScene::~CameraScene()
{

}

void CameraScene::Update(float deltaTime) //카메라는 타겟의 트랜스폼을 자기거처럼 사용하는거지?
{
	D2D1_MATRIX_3X2_F invserse = m_pOwner->m_Transform->m_WorldTransform;  
	D2D1InvertMatrix(&invserse); 
	D2DRenderer::m_CameraTransform = invserse * D2D1::Matrix3x2F::Translation(WinHalfSizeX, WinHalfSizeY); //카메라의 트랜스폼에서 처리하고있었네.. 
	m_ViewBoundBox->SetCenter(m_pOwner->m_Transform->m_WorldTransform.dx, m_pOwner->m_Transform->m_WorldTransform.dy);
	m_pOwner->m_pOwner->SetCullingBound(m_ViewBoundBox);
}




