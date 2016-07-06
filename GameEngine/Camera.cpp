#include"Camera.h"

MyCamera::MyCamera()
{
	m_cameraType = AIRCRAFT;

	m_pos = D3DXVECTOR3(0.0f, 40.0f, 0.0f);
	m_right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	m_up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_look = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
}

MyCamera::MyCamera(CameraType cameraType)
{
	m_cameraType = cameraType;

	m_pos = D3DXVECTOR3(0.0f, 40.0f, 0.0f);
	m_right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	m_up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_look = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
}

MyCamera::~MyCamera()
{

}

//前进后退
void MyCamera::walk(float units)
{
	if (m_cameraType == LANDOBJECT)
		m_pos += D3DXVECTOR3(m_look.x, 0.0f, m_look.z) * units;

	if (m_cameraType == AIRCRAFT)
		m_pos += m_look * units;
}
//左右移动
void MyCamera::strafe(float units)
{
	if (m_cameraType == LANDOBJECT)
		m_pos += D3DXVECTOR3(m_right.x, 0.0f, m_right.z) * units;

	if (m_cameraType == AIRCRAFT)
		m_pos += m_right * units;
}
//上下移动
void MyCamera::fly(float units)
{
	if (m_cameraType == LANDOBJECT)
		m_pos.y += units;

	if (m_cameraType == AIRCRAFT)
		m_pos += m_up * units;
}
//绕x轴旋转
void MyCamera::pitch(float angle)
{
	D3DXMATRIX T;
	D3DXMatrixRotationAxis(&T, &m_right, angle);

	D3DXVec3TransformCoord(&m_up, &m_up, &T);
	D3DXVec3TransformCoord(&m_look, &m_look, &T);
}
//绕y轴旋转
void MyCamera::yaw(float angle)
{
	D3DXMATRIX T;
	if (m_cameraType == LANDOBJECT)
		D3DXMatrixRotationY(&T, angle);

	if (m_cameraType == AIRCRAFT)
		D3DXMatrixRotationAxis(&T, &m_up, angle);

	D3DXVec3TransformCoord(&m_right, &m_right, &T);
	D3DXVec3TransformCoord(&m_look, &m_look, &T);
}
//绕z轴旋转
void MyCamera::roll(float angle)
{
	if (m_cameraType == AIRCRAFT)
	{
		D3DXMATRIX T;
		D3DXMatrixRotationAxis(&T, &m_look, angle);

		D3DXVec3TransformCoord(&m_right, &m_right, &T);
		D3DXVec3TransformCoord(&m_up, &m_up, &T);
	}
}
//获取视图变换矩阵
void MyCamera::getViewMatrix(MyMatrix4x4& view)
{
	D3DXVec3Normalize(&m_look, &m_look);

	D3DXVec3Cross(&m_up, &m_look, &m_right);
	D3DXVec3Normalize(&m_up, &m_up);

	D3DXVec3Cross(&m_right, &m_up, &m_look);
	D3DXVec3Normalize(&m_right, &m_right);

	float x = -D3DXVec3Dot(&m_right, &m_pos);
	float y = -D3DXVec3Dot(&m_up, &m_pos);
	float z = -D3DXVec3Dot(&m_look, &m_pos);

	view = MyMatrix4x4(m_right.x, m_up.x, m_look.x, 0.0f,
		m_right.y, m_up.y, m_look.y, 0.0f,
		m_right.z, m_up.z, m_look.z, 0.0f,
		x, y, z, 1.0f);
}

void MyCamera::setCameraType(CameraType cameraType)
{
	m_cameraType = cameraType;
}

void MyCamera::getPosition(D3DXVECTOR3* pos)
{
	*pos = m_pos;
}

void MyCamera::setPosition(D3DXVECTOR3* pos)
{
	m_pos = *pos;
}

void MyCamera::getRight(D3DXVECTOR3* right)
{
	*right = m_right;
}

void MyCamera::getUp(D3DXVECTOR3* up)
{
	*up = m_up;
}

void MyCamera::getLook(D3DXVECTOR3* look)
{
	*look = m_look;
}

