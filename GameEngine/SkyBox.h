#pragma once
#include "defines.h"
#include "d3dx9.h"
#include <vector>

//Ϊ��պ��ඨ��һ��FVF�����ʽ
struct SKYBOXVERTEX
{
	float	x, y, z;
	float	u, v;
};
#define D3DFVF_SKYBOX D3DFVF_XYZ|D3DFVF_TEX1


class MySkyBox
{
private:
	LPDIRECT3DDEVICE9 m_pd3dDevice;	//D3D�豸����
	LPDIRECT3DVERTEXBUFFER9	m_pVertexBuffer;	//���㻺�����
	LPDIRECT3DTEXTURE9 m_pTexture[5];	//5������ӿڶ���
	float m_Length;	//��պб߳�
public:
	MySkyBox(LPDIRECT3DDEVICE9  pDevice);
	virtual ~MySkyBox(void);
	void Shutdown();
	bool InitSkyBox(float Length);
	bool LoadSkyTextureFromFile(std::vector<char *> skyName);
	void RenderSkyBox(D3DXMATRIX *pMatWorld, bool bRenderFrame);
};

