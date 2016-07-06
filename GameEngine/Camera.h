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
		LANDOBJECT =0, //½
		AIRCRAFT
	};	//����

	MyCamera();
	MyCamera(CameraType cameraType);
	~MyCamera();
	//����
	void strafe(float units);
	//����
	void fly(float units);
	//ֱ��
	void walk(float units);
	//��x����ת
	void pitch(float angles);
	//��y����ת
	void yaw(float angles);
	//��z����ת
	void roll(float angles);
	//��ȡ��ͼ�任����
	void getViewMatrix(MyMatrix4x4& V);
	//�������������
	void setCameraType(CameraType cameraType);
	//��ȡ�����λ��
	void getPosition(D3DXVECTOR3* pos);
	//���������λ��
	void setPosition(D3DXVECTOR3* pos);
	//��ȡ�����ˮƽ����
	void getRight(D3DXVECTOR3* right);
	//��ȡ�������ֱ����
	void getUp(D3DXVECTOR3* up);
	//��ȡ�������������
	void getLook(D3DXVECTOR3* look);
	//��ȡ�����λ��
	MyVector3 getCameraPos() {
		return D3DtoMyVector(m_pos);
	}
	void setCameraPos(MyVector3 &pos) {
		m_pos = MytoD3DVector(pos);
	}
	//��ȡ�������������
	MyVector3 getCameraLook() {
		return D3DtoMyVector(m_look);
	}
	//��ȡ�������ֱ����
	MyVector3 getCameraUp() {
		return D3DtoMyVector(m_up);
	}
	//��ȡ�����ˮƽ����
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