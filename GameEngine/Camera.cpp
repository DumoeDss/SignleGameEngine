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


// ���ݸ����ľ�������ȡ���任����
VOID MyCamera::CalculateViewMatrix(D3DXMATRIX *pMatrix)
{
	//1.�Ȱ�3���������淶����ʹ���໥��ֱ����Ϊһ����������
	D3DXVec3Normalize(&m_vLookVector, &m_vLookVector);  //�淶���۲����
	D3DXVec3Cross(&m_vUpVector, &m_vLookVector, &m_vRightVector);    // ��������۲�������ֱ
	D3DXVec3Normalize(&m_vUpVector, &m_vUpVector);                // �淶��������
	D3DXVec3Cross(&m_vRightVector, &m_vUpVector, &m_vLookVector);    // ����������������ֱ
	D3DXVec3Normalize(&m_vRightVector, &m_vRightVector);          // �淶��������


	// 2.������ȡ���任����
	//����д��ȡ���任����ĵ�һ��
	pMatrix->_11 = m_vRightVector.x;           // Rx
	pMatrix->_12 = m_vUpVector.x;              // Ux
	pMatrix->_13 = m_vLookVector.x;            // Lx
	pMatrix->_14 = 0.0f;
	//����д��ȡ���任����ĵڶ���
	pMatrix->_21 = m_vRightVector.y;           // Ry
	pMatrix->_22 = m_vUpVector.y;              // Uy
	pMatrix->_23 = m_vLookVector.y;            // Ly
	pMatrix->_24 = 0.0f;
	//����д��ȡ���任����ĵ�����
	pMatrix->_31 = m_vRightVector.z;           // Rz
	pMatrix->_32 = m_vUpVector.z;              // Uz
	pMatrix->_33 = m_vLookVector.z;            // Lz
	pMatrix->_34 = 0.0f;
	//����д��ȡ���任����ĵ�����
	pMatrix->_41 = -D3DXVec3Dot(&m_vRightVector, &m_vCameraPosition);    // -P*R
	pMatrix->_42 = -D3DXVec3Dot(&m_vUpVector, &m_vCameraPosition);       // -P*U
	pMatrix->_43 = -D3DXVec3Dot(&m_vLookVector, &m_vCameraPosition);     // -P*L
	pMatrix->_44 = 1.0f;
}


// ����������Ĺ۲�λ��
VOID MyCamera::SetTargetPosition(D3DXVECTOR3 *pLookat)
{
	//�ȿ���pLookat�Ƿ�ΪĬ��ֵNULL
	if (pLookat != NULL)  m_vTargetPosition = (*pLookat);
	else m_vTargetPosition = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	m_vLookVector = m_vTargetPosition - m_vCameraPosition;//�۲��λ�ü������λ�ã��õ��۲췽������
	D3DXVec3Normalize(&m_vLookVector, &m_vLookVector);//�淶��m_vLookVector����

													  //�������淶��m_vUpVector��m_vRightVector
	D3DXVec3Cross(&m_vUpVector, &m_vLookVector, &m_vRightVector);
	D3DXVec3Normalize(&m_vUpVector, &m_vUpVector);
	D3DXVec3Cross(&m_vRightVector, &m_vUpVector, &m_vLookVector);
	D3DXVec3Normalize(&m_vRightVector, &m_vRightVector);
}

// ������������ڵ�λ��
VOID MyCamera::SetCameraPosition(D3DXVECTOR3 *pVector)
{
	D3DXVECTOR3 V = D3DXVECTOR3(0.0f, 0.0f, -250.0f);
	m_vCameraPosition = pVector ? (*pVector) : V;//��Ŀ����������pVectorΪ��Ļ���
												 //����*pVector��ֵ����m_vCameraPosition=*pVector����
												 //���򷵻�V��ֵ����m_vCameraPosition=V��
}

// ����ȡ���任����
VOID MyCamera::SetViewMatrix(D3DXMATRIX *pMatrix)
{
	//����pMatrix��ֵ����һ���ж�
	if (pMatrix) m_matView = *pMatrix;
	else CalculateViewMatrix(&m_matView);
	//m_pd3dDevice->SetTransform(D3DTS_VIEW, &m_matView);
	//��ȡ���任�����ֵ�������ֱ���ҷ������Ϸ������͹۲����
	m_vRightVector = D3DXVECTOR3(m_matView._11, m_matView._12, m_matView._13);
	m_vUpVector = D3DXVECTOR3(m_matView._21, m_matView._22, m_matView._23);
	m_vLookVector = D3DXVECTOR3(m_matView._31, m_matView._32, m_matView._33);
}

// ����ͶӰ�任����
VOID MyCamera::SetProjMatrix(D3DXMATRIX *pMatrix)
{
	//�ж�ֵ��û�У�û�еĻ��ͼ���һ��
	if (pMatrix != NULL) m_matProj = *pMatrix;
	else D3DXMatrixPerspectiveFovLH(&m_matProj, D3DX_PI / 4.0f, (float)((double)WINDOW_WIDTH / WINDOW_HEIGHT), 1.0f, 300000.0f);//�ӽ���Զ�����һ�㣬�����Ͳ��¿�����Զ����������
	//m_pd3dDevice->SetTransform(D3DTS_PROJECTION, &m_matProj);//����ͶӰ�任����
}

// ��������ƽ��fUnits����λ
VOID MyCamera::MoveAlongRightVec(FLOAT fUnits)
{
	//ֱ�ӳ���fUnits�������ۼӾ�����
	m_vCameraPosition += m_vRightVector * fUnits;
	m_vTargetPosition += m_vRightVector * fUnits;
}

// ��������ƽ��fUnits����λ
VOID MyCamera::MoveAlongUpVec(FLOAT fUnits)
{
	//ֱ�ӳ���fUnits�������ۼӾ�����
	m_vCameraPosition += m_vUpVector * fUnits;
	m_vTargetPosition += m_vUpVector * fUnits;
}

// �ع۲�����ƽ��fUnits����λ
VOID MyCamera::MoveAlongLookVec(FLOAT fUnits)
{
	//ֱ�ӳ���fUnits�������ۼӾ�����
	m_vCameraPosition += m_vLookVector * fUnits;
	m_vTargetPosition += m_vLookVector * fUnits;
}

// ����������תfAngle�����ȵ�λ�ĽǶ�
VOID MyCamera::RotationRightVec(FLOAT fAngle)
{
	D3DXMATRIX R;
	D3DXMatrixRotationAxis(&R, &m_vRightVector, fAngle);//��������m_vRightVector��תfAngle���Ƕȵ�R����
	D3DXVec3TransformCoord(&m_vUpVector, &m_vUpVector, &R);//��m_vUpVector������m_vRightVector��תfAngle���Ƕ�
	D3DXVec3TransformCoord(&m_vLookVector, &m_vLookVector, &R);//��m_vLookVector������m_vRightVector��תfAngle���Ƕ�

	m_vTargetPosition = m_vLookVector * D3DXVec3Length(&m_vCameraPosition);//����һ�¹۲�����λ�ã��������ģ=������
}

// ����������תfAngle�����ȵ�λ�ĽǶ�
VOID MyCamera::RotationUpVec(FLOAT fAngle)
{
	D3DXMATRIX R;
	D3DXMatrixRotationAxis(&R, &m_vUpVector, fAngle);//��������m_vUpVector��תfAngle���Ƕȵ�R����
	D3DXVec3TransformCoord(&m_vRightVector, &m_vRightVector, &R);//��m_vRightVector������m_vUpVector��תfAngle���Ƕ�
	D3DXVec3TransformCoord(&m_vLookVector, &m_vLookVector, &R);//��m_vLookVector������m_vUpVector��תfAngle���Ƕ�

	m_vTargetPosition = m_vLookVector * D3DXVec3Length(&m_vCameraPosition);//����һ�¹۲�����λ�ã��������ģ=������
}

//  �ع۲�������תfAngle�����ȵ�λ�ĽǶ�
VOID MyCamera::RotationLookVec(FLOAT fAngle)
{
	D3DXMATRIX R;
	D3DXMatrixRotationAxis(&R, &m_vLookVector, fAngle);//��������m_vLookVector��תfAngle���Ƕȵ�R����
	D3DXVec3TransformCoord(&m_vRightVector, &m_vRightVector, &R);//��m_vRightVector������m_vLookVector��תfAngle���Ƕ�
	D3DXVec3TransformCoord(&m_vUpVector, &m_vUpVector, &R);//��m_vUpVector������m_vLookVector��תfAngle���Ƕ�

	m_vTargetPosition = m_vLookVector * D3DXVec3Length(&m_vCameraPosition);//����һ�¹۲�����λ�ã��������ģ=������
}
