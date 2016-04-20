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
	  // 沿各分量平移的三个函数
	  void MoveAlongRightVec(FLOAT fUnits);   // 沿right向量移动
	  void MoveAlongUpVec(FLOAT fUnits);      // 沿up向量移动
	  void MoveAlongLookVec(FLOAT fUnits);    // 沿look向量移动
	  // 绕各分量旋转的三个函数
	  void RotationRightVec(FLOAT fAngle);    // 绕right向量旋转
	  void RotationUpVec(FLOAT fAngle);       // 绕up向量旋转
	  void RotationLookVec(FLOAT fAngle);     // 绕look向量旋转

	  void CalculateViewMatrix(D3DXMATRIX *pMatrix);    //计算取景变换矩阵

	  void GetProjMatrix(D3DXMATRIX *pMatrix) { *pMatrix = m_matProj; }  //返回当前投影矩阵
	  void GetCameraPosition(D3DXVECTOR3 *pVector) { *pVector = m_vCameraPosition; } //返回当前摄像机位置矩阵
	  void GetLookVector(D3DXVECTOR3 *pVector) { *pVector = m_vLookVector; }  //返回当前的观察矩阵

	  void SetTargetPosition(D3DXVECTOR3 *pLookat = NULL);  //设置摄像机的目标观察位置向量
	  void SetCameraPosition(D3DXVECTOR3 *pVector = NULL); //设置摄像机所在的位置向量
	  void SetViewMatrix(D3DXMATRIX *pMatrix = NULL);  //设置取景变换矩阵
	  void SetProjMatrix(D3DXMATRIX *pMatrix = NULL);  //设置投影变换矩阵

      MyVector3 m_pos, m_view, m_up;

	  //成员变量的声明
	  D3DXVECTOR3 m_vRightVector;        // 右分量向量
	  D3DXVECTOR3 m_vUpVector;           // 上分量向量
	  D3DXVECTOR3 m_vLookVector;         // 观察方向向量
	  D3DXVECTOR3 m_vCameraPosition;        // 摄像机位置的向量
	  D3DXVECTOR3 m_vTargetPosition;        //目标观察位置的向量
	  D3DXMATRIX m_matView;          // 取景变换矩阵
	  D3DXMATRIX m_matProj;          // 投影变换矩阵  
};
