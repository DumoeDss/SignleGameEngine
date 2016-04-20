#pragma once

#include<math.h>
#include"Vector.h"
#include <d3d9.h>
#include <d3dx9.h>

class MyCamera
{
   public:
      MyCamera() {}

      void SetCamera(float x, float y, float z,
                     float xv, float yv, float zv,
                     float xu, float yu, float zu);

      void MoveCamera(float amount);
      void RotateCamera(float angle, float X, float Y, float Z);
	  // �ظ�����ƽ�Ƶ���������
	  void MoveAlongRightVec(FLOAT fUnits);   // ��right�����ƶ�
	  void MoveAlongUpVec(FLOAT fUnits);      // ��up�����ƶ�
	  void MoveAlongLookVec(FLOAT fUnits);    // ��look�����ƶ�
	  // �Ƹ�������ת����������
	  void RotationRightVec(FLOAT fAngle);    // ��right������ת
	  void RotationUpVec(FLOAT fAngle);       // ��up������ת
	  void RotationLookVec(FLOAT fAngle);     // ��look������ת

	  void CalculateViewMatrix(D3DXMATRIX *pMatrix);    //����ȡ���任����

	  void GetProjMatrix(D3DXMATRIX *pMatrix) { *pMatrix = m_matProj; }  //���ص�ǰͶӰ����
	  void GetCameraPosition(D3DXVECTOR3 *pVector) { *pVector = m_vCameraPosition; } //���ص�ǰ�����λ�þ���
	  void GetLookVector(D3DXVECTOR3 *pVector) { *pVector = m_vLookVector; }  //���ص�ǰ�Ĺ۲����

	  void SetTargetPosition(D3DXVECTOR3 *pLookat = NULL);  //�����������Ŀ��۲�λ������
	  void SetCameraPosition(D3DXVECTOR3 *pVector = NULL); //������������ڵ�λ������
	  void SetViewMatrix(D3DXMATRIX *pMatrix = NULL);  //����ȡ���任����
	  void SetProjMatrix(D3DXMATRIX *pMatrix = NULL);  //����ͶӰ�任����

      MyVector3 m_pos, m_view, m_up;

	  //��Ա����������
	  D3DXVECTOR3 m_vRightVector;        // �ҷ�������
	  D3DXVECTOR3 m_vUpVector;           // �Ϸ�������
	  D3DXVECTOR3 m_vLookVector;         // �۲췽������
	  D3DXVECTOR3 m_vCameraPosition;        // �����λ�õ�����
	  D3DXVECTOR3 m_vTargetPosition;        //Ŀ��۲�λ�õ�����
	  D3DXMATRIX m_matView;          // ȡ���任����
	  D3DXMATRIX m_matProj;          // ͶӰ�任����  
};
