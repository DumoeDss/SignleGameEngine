#pragma once

#include<math.h>
#include"Vector.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "MathLibrary.h"

class MyCamera
{
public:
	enum CameraType { 
		LANDOBJECT =0, //陆
		AIRCRAFT
	};	//飞行

	MyCamera();
	MyCamera(CameraType cameraType);
	~MyCamera();
	//左右
	void strafe(float units);
	//上下
	void fly(float units);
	//直行
	void walk(float units);
	//绕x轴旋转
	void pitch(float angles);
	//绕y轴旋转
	void yaw(float angles);
	//绕z轴旋转
	void roll(float angles);
	//获取视图变换矩阵
	void getViewMatrix(MyMatrix4x4& V);
	//设置摄像机类型
	void setCameraType(CameraType cameraType);
	//获取摄像机位置
	void getPosition(D3DXVECTOR3* pos);
	//设置摄像机位置
	void setPosition(D3DXVECTOR3* pos);
	//获取摄像机水平向量
	void getRight(D3DXVECTOR3* right);
	//获取摄像机竖直向量
	void getUp(D3DXVECTOR3* up);
	//获取摄像机朝向向量
	void getLook(D3DXVECTOR3* look);
	//获取摄像机位置
	MyVector3 getCameraPos() {
		return D3DtoMyVector(m_pos);
	}
	void setCameraPos(MyVector3 &pos) {
		m_pos = MytoD3DVector(pos);
	}
	//获取摄像机朝向向量
	MyVector3 getCameraLook() {
		return D3DtoMyVector(m_look);
	}
	//获取摄像机竖直向量
	MyVector3 getCameraUp() {
		return D3DtoMyVector(m_up);
	}
	//获取摄像机水平向量
	MyVector3 getCameraRight() {
		return D3DtoMyVector(m_right);
	}

	D3DXVECTOR3 MytoD3DVector(const MyVector3 &myVec) {
		return D3DXVECTOR3(myVec.x, myVec.y, myVec.z);
	}

	MyVector3 D3DtoMyVector(const D3DXVECTOR3 &d3dVec) {
		return MyVector3(d3dVec.x, d3dVec.y, d3dVec.z);
	}

private:
	CameraType  m_cameraType;
	D3DXVECTOR3 m_right;
	D3DXVECTOR3 m_up;
	D3DXVECTOR3 m_look;
	D3DXVECTOR3 m_pos;
};