#include"Camera.h"


void MyCamera::SetCamera(float x, float y, float z,
                        float xv, float yv, float zv,
                        float xu, float yu, float zu)
{
   m_pos.x = x; m_pos.y = y; m_pos.z = z;
   m_view.x = xv; m_view.y = yv; m_view.z = zv;
   m_up.x = xu; m_up.y = yu; m_up.z = zu;
}


void MyCamera::MoveCamera(float amount)
{
   MyVector3 dir = m_view - m_pos;
   dir.Normal();

	m_pos += dir * amount;

    m_view += dir * amount;
}


void MyCamera::RotateCamera(float angle, float X, float Y, float Z)
{
   float ca = (float)cos(angle);
   float sa = (float)sin(angle);

	MyVector3 dir = m_view - m_pos;
	dir.Normal();

   MyVector3 dir2;

	dir2.x = (ca + (1 - ca) * X) * dir.x;
	dir2.x += ((1 - ca) * X * Y - Z * sa)* dir.y;
	dir2.x += ((1 - ca) * X * Z + Y * sa) * dir.z;

	dir2.y = ((1 - ca) * X * Y + Z * sa) * dir.x;
	dir2.y += (ca + (1 - ca) * Y) * dir.y;
	dir2.y += ((1 - ca) * Y * Z - X * sa) * dir.z;

	dir2.z = ((1 - ca) * X * Z - Y * sa) * dir.x;
	dir2.z += ((1 - ca) * Y * Z + X * sa) * dir.y;
	dir2.z += (ca + (1 - ca) * Z) * dir.z;

	m_view = m_pos + dir2;
}


#ifndef WINDOW_WIDTH
#define WINDOW_WIDTH	1366						 
#define WINDOW_HEIGHT	768					 
#endif


// 根据给定的矩阵计算出取景变换矩阵
VOID MyCamera::CalculateViewMatrix(D3DXMATRIX *pMatrix)
{
	//1.先把3个向量都规范化并使其相互垂直，成为一组正交矩阵
	D3DXVec3Normalize(&m_vLookVector, &m_vLookVector);  //规范化观察分量
	D3DXVec3Cross(&m_vUpVector, &m_vLookVector, &m_vRightVector);    // 上向量与观察向量垂直
	D3DXVec3Normalize(&m_vUpVector, &m_vUpVector);                // 规范化上向量
	D3DXVec3Cross(&m_vRightVector, &m_vUpVector, &m_vLookVector);    // 右向量与上向量垂直
	D3DXVec3Normalize(&m_vRightVector, &m_vRightVector);          // 规范化右向量


	// 2.创建出取景变换矩阵
	//依次写出取景变换矩阵的第一行
	pMatrix->_11 = m_vRightVector.x;           // Rx
	pMatrix->_12 = m_vUpVector.x;              // Ux
	pMatrix->_13 = m_vLookVector.x;            // Lx
	pMatrix->_14 = 0.0f;
	//依次写出取景变换矩阵的第二行
	pMatrix->_21 = m_vRightVector.y;           // Ry
	pMatrix->_22 = m_vUpVector.y;              // Uy
	pMatrix->_23 = m_vLookVector.y;            // Ly
	pMatrix->_24 = 0.0f;
	//依次写出取景变换矩阵的第三行
	pMatrix->_31 = m_vRightVector.z;           // Rz
	pMatrix->_32 = m_vUpVector.z;              // Uz
	pMatrix->_33 = m_vLookVector.z;            // Lz
	pMatrix->_34 = 0.0f;
	//依次写出取景变换矩阵的第四行
	pMatrix->_41 = -D3DXVec3Dot(&m_vRightVector, &m_vCameraPosition);    // -P*R
	pMatrix->_42 = -D3DXVec3Dot(&m_vUpVector, &m_vCameraPosition);       // -P*U
	pMatrix->_43 = -D3DXVec3Dot(&m_vLookVector, &m_vCameraPosition);     // -P*L
	pMatrix->_44 = 1.0f;
}


// 设置摄像机的观察位置
VOID MyCamera::SetTargetPosition(D3DXVECTOR3 *pLookat)
{
	//先看看pLookat是否为默认值NULL
	if (pLookat != NULL)  m_vTargetPosition = (*pLookat);
	else m_vTargetPosition = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	m_vLookVector = m_vTargetPosition - m_vCameraPosition;//观察点位置减摄像机位置，得到观察方向向量
	D3DXVec3Normalize(&m_vLookVector, &m_vLookVector);//规范化m_vLookVector向量

													  //正交并规范化m_vUpVector和m_vRightVector
	D3DXVec3Cross(&m_vUpVector, &m_vLookVector, &m_vRightVector);
	D3DXVec3Normalize(&m_vUpVector, &m_vUpVector);
	D3DXVec3Cross(&m_vRightVector, &m_vUpVector, &m_vLookVector);
	D3DXVec3Normalize(&m_vRightVector, &m_vRightVector);
}

// 设置摄像机所在的位置
VOID MyCamera::SetCameraPosition(D3DXVECTOR3 *pVector)
{
	D3DXVECTOR3 V = D3DXVECTOR3(0.0f, 0.0f, -250.0f);
	m_vCameraPosition = pVector ? (*pVector) : V;//三目运算符，如果pVector为真的话，
												 //返回*pVector的值（即m_vCameraPosition=*pVector），
												 //否则返回V的值（即m_vCameraPosition=V）
}

// 设置取景变换矩阵
VOID MyCamera::SetViewMatrix(D3DXMATRIX *pMatrix)
{
	//根据pMatrix的值先做一下判断
	if (pMatrix) m_matView = *pMatrix;
	else CalculateViewMatrix(&m_matView);
	//m_pd3dDevice->SetTransform(D3DTS_VIEW, &m_matView);
	//把取景变换矩阵的值分下来分别给右分量，上分量，和观察分量
	m_vRightVector = D3DXVECTOR3(m_matView._11, m_matView._12, m_matView._13);
	m_vUpVector = D3DXVECTOR3(m_matView._21, m_matView._22, m_matView._23);
	m_vLookVector = D3DXVECTOR3(m_matView._31, m_matView._32, m_matView._33);
}

// 设置投影变换矩阵
VOID MyCamera::SetProjMatrix(D3DXMATRIX *pMatrix)
{
	//判断值有没有，没有的话就计算一下
	if (pMatrix != NULL) m_matProj = *pMatrix;
	else D3DXMatrixPerspectiveFovLH(&m_matProj, D3DX_PI / 4.0f, (float)((double)WINDOW_WIDTH / WINDOW_HEIGHT), 1.0f, 300000.0f);//视截体远景设大一点，这样就不怕看不到远处的物体了
	//m_pd3dDevice->SetTransform(D3DTS_PROJECTION, &m_matProj);//设置投影变换矩阵
}

// 沿右向量平移fUnits个单位
VOID MyCamera::MoveAlongRightVec(FLOAT fUnits)
{
	//直接乘以fUnits的量来累加就行了
	m_vCameraPosition += m_vRightVector * fUnits;
	m_vTargetPosition += m_vRightVector * fUnits;
}

// 沿上向量平移fUnits个单位
VOID MyCamera::MoveAlongUpVec(FLOAT fUnits)
{
	//直接乘以fUnits的量来累加就行了
	m_vCameraPosition += m_vUpVector * fUnits;
	m_vTargetPosition += m_vUpVector * fUnits;
}

// 沿观察向量平移fUnits个单位
VOID MyCamera::MoveAlongLookVec(FLOAT fUnits)
{
	//直接乘以fUnits的量来累加就行了
	m_vCameraPosition += m_vLookVector * fUnits;
	m_vTargetPosition += m_vLookVector * fUnits;
}

// 沿右向量旋转fAngle个弧度单位的角度
VOID MyCamera::RotationRightVec(FLOAT fAngle)
{
	D3DXMATRIX R;
	D3DXMatrixRotationAxis(&R, &m_vRightVector, fAngle);//创建出绕m_vRightVector旋转fAngle个角度的R矩阵
	D3DXVec3TransformCoord(&m_vUpVector, &m_vUpVector, &R);//让m_vUpVector向量绕m_vRightVector旋转fAngle个角度
	D3DXVec3TransformCoord(&m_vLookVector, &m_vLookVector, &R);//让m_vLookVector向量绕m_vRightVector旋转fAngle个角度

	m_vTargetPosition = m_vLookVector * D3DXVec3Length(&m_vCameraPosition);//更新一下观察点的新位置（方向乘以模=向量）
}

// 沿上向量旋转fAngle个弧度单位的角度
VOID MyCamera::RotationUpVec(FLOAT fAngle)
{
	D3DXMATRIX R;
	D3DXMatrixRotationAxis(&R, &m_vUpVector, fAngle);//创建出绕m_vUpVector旋转fAngle个角度的R矩阵
	D3DXVec3TransformCoord(&m_vRightVector, &m_vRightVector, &R);//让m_vRightVector向量绕m_vUpVector旋转fAngle个角度
	D3DXVec3TransformCoord(&m_vLookVector, &m_vLookVector, &R);//让m_vLookVector向量绕m_vUpVector旋转fAngle个角度

	m_vTargetPosition = m_vLookVector * D3DXVec3Length(&m_vCameraPosition);//更新一下观察点的新位置（方向乘以模=向量）
}

//  沿观察向量旋转fAngle个弧度单位的角度
VOID MyCamera::RotationLookVec(FLOAT fAngle)
{
	D3DXMATRIX R;
	D3DXMatrixRotationAxis(&R, &m_vLookVector, fAngle);//创建出绕m_vLookVector旋转fAngle个角度的R矩阵
	D3DXVec3TransformCoord(&m_vRightVector, &m_vRightVector, &R);//让m_vRightVector向量绕m_vLookVector旋转fAngle个角度
	D3DXVec3TransformCoord(&m_vUpVector, &m_vUpVector, &R);//让m_vUpVector向量绕m_vLookVector旋转fAngle个角度

	m_vTargetPosition = m_vLookVector * D3DXVec3Length(&m_vCameraPosition);//更新一下观察点的新位置（方向乘以模=向量）
}
