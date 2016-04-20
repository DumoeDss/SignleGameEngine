#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "RenderInterface.h"
#include "XMesh.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

struct myD3DStaticBuffer
{
	myD3DStaticBuffer() : vbPtr(0), ibPtr(0), numVerts(0),
		numIndices(0),stride(0),fvf(0),primType(NULL_TYPE){}

	LPDIRECT3DVERTEXBUFFER9 vbPtr;
	LPDIRECT3DINDEXBUFFER9 ibPtr;
	int numVerts;
	int numIndices;
	int stride;
	unsigned long fvf;
	PrimType primType;
};

struct myD3DTexture
{
	char *fileName;
	int width, height;
	LPDIRECT3DTEXTURE9 image;
};

class MyD3DRenderer : public MyRenderInterface
{
public:
	MyD3DRenderer();
	~MyD3DRenderer();

	bool Initialize(int w, int h, WinHWND mainWin, bool fullScreen, UGP_MS_TYPE ms);

	void SetClearCol(float r, float g, float b);
	void Shutdown();
	void StartRender(bool bColor, bool bDepth, bool bStencil);
	
	void EndRendering();
	void ClearBuffers(bool bColor, bool bDepth, bool bStencil);

	int CreateStaticBuffer(VertexType, PrimType, 
		int totalVerts, int totalIndices,
		int stride, void **data, unsigned int *indices, int *staticId);

	void SetMaterial(myMaterial *mat);

	void SetLight(myLight *light, int index);
	void DisabledLight(int index);

	void SetTranspency(RenderState state, TransState src, TransState dst);

	void EnableFog(float start, float end, UGP_FOG_TYPE type, 
		unsigned long color, bool rangeFog);
	void DisableFog();

	int AddTexture2D(char *file, int *texId);
	void SetTextureFilter(int index, int filter, int val);
	void SetMultiTexture();
	void SetDetailMapping();
	void ApplyTexture(int index, int texId);
	void SaveScreenShot(char *file);
	void EnablePointSprites(float size, float min, float a, float b, float c);
	void DisablePointSprites();

	bool CreateText(char *font, int weight, bool italic, int size, int &id);
	void DisplayText(int id, long x, long y, int r, int g, int b, char *text, ...);
	void DisplayText(int id, long x, long y, unsigned long color, char *text, ...);


	bool AddGUIBackdrop(int guiId, char *fileName);
	bool AddGUIStaticText(int guiId, int id,
		char *text, int x, int y, unsigned long color,
		int fontID);
	bool AddGUIButton(int guiId, int id, int x, int y,
		char *up, char *over, char *down);
	void ProcessGUI(int guiId, bool LMBDown,
		int mouseX, int mouseY,
		void(*funcPtr)(int id, int state));

	void CalculateProjMatrix(float fov,float n, float f);
	void CalculateOrthoMatrix(float n, float f);

	int LoadXModel(char *file, int *xModelId);
	int LoadXModel(char *file, int xModelId);

	void ReleaseAllStaticBuffers();
	void ReleaseAllXModels();
	int ReleaseStaticBuffer(int staticID);
	int ReleaseXModel(int xModelId);

	int RenderStaticBuffer(int staticId);
	int RenderXModel(int xModelId);

	void GetXModelBoundingSphere(int xModelId, MyVector3 *origin, float *radius)
	{
		if(xModelId < 0 || xModelId >= m_numXModels || !m_xModels)
			return;

		D3DXVECTOR3 center;
		float r;

		m_xModels[xModelId].GetBoundingSphere(&center,&r);

		if(origin)
		{
			origin->x = center.x;
			origin->y = center.y;
			origin->z = center.z;
		}
		if(radius)
			*radius = r;
	}

	void UpdateXAnimation(int xModelId, float time, MyMatrix4x4 *mat)
	{
		if(xModelId <0 || xModelId >= m_numXModels || !m_xModels)
			return;

		if(!mat) return;

		m_xModels[xModelId].Update(time,(D3DXMATRIX*)&mat->matrix);
	}

	void ApplyView(MyVector3 pos, MyVector3 view, MyVector3 up);
	void SetWorldMatrix(MyMatrix4x4 *mat);
	void CameraToViewMatrix(MyCamera *cam, MyMatrix4x4 *mat);
	void GetProjectMatrix(MyMatrix4x4 *mat);

	//天空盒
	bool InitSkyBox(float Length);
	bool LoadSkyTextureFromFile(char *pFrontTextureFile, char *pBackTextureFile, char *pLeftTextureFile, char *pRightTextureFile, char *pTopTextureFile);
	void RenderSkyBox(D3DXMATRIX *pMatWorld, bool bRenderFrame);

private:
	void OneTimeInit();
private:
	D3DCOLOR m_Color;
	LPDIRECT3D9 m_Direct3D;
	LPDIRECT3DDEVICE9 m_Device;
	bool m_renderingScene;

	D3DXMATRIX m_projection;

	LPD3DXFONT *m_fonts;

	myD3DStaticBuffer *m_staticBufferList;
	int m_numStaticBuffers;
	int m_activeStaticBuffer;

	MyXModel *m_xModels;
	int m_numXModels;

	myD3DTexture *m_textureList;
	unsigned int m_numTextures;

	LPDIRECT3DVERTEXBUFFER9	m_skyVertexBuffer;		//顶点缓存对象
	LPDIRECT3DTEXTURE9 m_skyTexture[5];			//5个纹理接口对象
	float m_Length;					//天空盒边长
};

bool CreateD3DRenderer(MyRenderInterface **pObj);
