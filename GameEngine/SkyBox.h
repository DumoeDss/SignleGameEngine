#pragma once
#include "defines.h"
#include "d3dx9.h"
#include <vector>

//为天空盒类定义一个FVF灵活顶点格式
struct SKYBOXVERTEX
{
	float	x, y, z;
	float	u, v;
};
#define D3DFVF_SKYBOX D3DFVF_XYZ|D3DFVF_TEX1


class MySkyBox
{
private:
	LPDIRECT3DDEVICE9 m_pd3dDevice;	//D3D设备对象
	LPDIRECT3DVERTEXBUFFER9	m_pVertexBuffer;	//顶点缓存对象
	LPDIRECT3DTEXTURE9 m_pTexture[5];	//5个纹理接口对象
	float m_Length;	//天空盒边长
public:
	MySkyBox(LPDIRECT3DDEVICE9  pDevice);
	virtual ~MySkyBox(void);
	void Shutdown();
	bool InitSkyBox(float Length);
	bool LoadSkyTextureFromFile(std::vector<char *> skyName);
	void RenderSkyBox(D3DXMATRIX *pMatWorld, bool bRenderFrame);
};

