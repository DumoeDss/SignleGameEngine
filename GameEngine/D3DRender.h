#pragma once

#include <vector>
#include <string>

#include <d3d9.h>
#include <d3dx9.h>

#include "Defines.h"
#include "XModel.h"
#include "GUI.h"
#include "Material.h"
#include "Light.h"
#include "Matrix.h"
#include "LogSystem.h"
#include "Particle.h"
  
class MySkyBox;
class MyLogSystem;
class MyTerrain;


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

class MyD3DRender// : public MyRenderInterface
{
public:
	MyD3DRender();
	~MyD3DRender();
	//初始化渲染引擎对象
	bool InitRender(int w, int h, WinHWND mainWin, bool fullScreen, MultiSampleType ms);
	//清屏
	void SetClearCol(float r, float g, float b);
	//释放资源
	void Shutdown();
	//开始渲染
	void StartRender(bool bColor, bool bDepth, bool bStencil);
	//结束渲染
	void EndRendering();
	//清除缓存
	void ClearBuffers(bool bColor, bool bDepth, bool bStencil);
	//创建静态缓存
	int CreateStaticBuffer(VertexType, PrimType, 
		int totalVerts, int totalIndices,
		int stride, void **data, unsigned int *indices, int *staticId);
	//设置材质
	void SetMaterial(myMaterial *mat);
	//设置光源
	void SetLight(myLight *light, int index);
	//关闭光源
	void DisabledLight(int index);
	//设置透明度
	void SetTranspency(RenderState state, TransState src, TransState dst);
	//打开雾效
	void EnableFog(float start, float end, FogType type, 
		unsigned long color, bool rangeFog);
	//关闭雾效
	void DisableFog();
	//添加纹理贴图
	int AddTexture2D(char *file, int *texId);
	//设置纹理过滤器
	void SetTextureFilter(int index, int filter, int val);
	//设置多重纹理
	void SetMultiTexture();
	void SetDetailMapping();
	//应用纹理贴图
	void ApplyTexture(int index, int texId);
	//截屏
	void SaveScreenShot(char *file);
	//激活点精灵
	void EnablePointSprites(float size, float min, float a, float b, float c);
	//关闭点精灵
	void DisablePointSprites();
	//创建文本
	bool CreateText(char *font, int weight, bool italic, int size, int &id);
	//显示文本
	void DisplayText(int id, long x, long y, int r, int g, int b, char *text, ...);
	void DisplayText(int id, long x, long y, unsigned long color, char *text, ...);
	//添加背景
	bool AddGUIBackdrop(int guiId, char *fileName);
	//添加静态文本
	bool AddGUIStaticText(int guiId, int id,
		char *text, int x, int y, unsigned long color,
		int fontID);
	//删除按钮
	bool DelGUIButton(int guiId, int id);
	//删除静态文本
	bool DelGUIStaticText(int guiId, int id);
	//添加按钮
	bool AddGUIButton(int guiId, int id, int x, int y,
		char *up, char *over, char *down);
	//渲染GUI
	void ProcessGUI(int guiId, bool LMBDown,
		int mouseX, int mouseY,
		void(*funcPtr)(int id, int state));
	LPDIRECT3DDEVICE9 GetDevice();
	//设置投影矩阵
	void CalculateProjMatrix(float fov,float n, float f);
	void CalculateOrthoMatrix(float n, float f);

	int RenderStaticBuffer(int staticId);
	//渲染模型
	int RenderXModel(int xModelId);

	//创建GUI
	bool CreateGUI(int &id)
	{
		if (!m_guiList)
		{
			m_guiList = new MyGUISystem[1];
			if (!m_guiList) return RE_FAIL;
		}
		else
		{
			MyGUISystem *temp;
			temp = new MyGUISystem[m_totalGUIs + 1];
			memcpy(temp, m_guiList, sizeof(MyGUISystem)*m_totalGUIs);
			delete[] m_guiList;
			m_guiList = temp;
		}
		id = m_totalGUIs;
		m_totalGUIs++;

		return true;
	}
	//释放GUI对象
	void ReleaseAllGUIs()
	{
		for (int s = 0; s<m_totalGUIs; s++)
		{
			m_guiList[s].Shutdown();
		}
		m_totalGUIs = 0;
		if (m_guiList) delete[] m_guiList;
		m_guiList = NULL;
	}

	void SetViewMatrix(MyMatrix4x4 *mat);
	void SetWorldMatrix(const MyMatrix4x4 *mat);
	void GetProjectMatrix(MyMatrix4x4 *mat);

	//粒子
	void InitParticle(int type, int length, int width,
		int height,char* fileName,int numParticles,MyVector3 pos);
	bool RenderParticle(float fElapsedTime);

	//天空盒
	bool InitSkyBox(float skyLen, std::vector<char *> skyName);
	bool RenderSkyBox(D3DXMATRIX *pMatWorld, bool bRenderFrame);
	//地形
	bool InitTerrain(std::string heightmapFileName,
		int numVertsPerRow,
		int numVertsPerCol,
		int cellSpacing,
		float heightScale,
		std::string textureFileName);
	void RenderTerrain(bool drawTris);
	float getHeight(float x, float z);
	//立方体 球体
	void InitObj(int type,MyVector3 pos, MyVector3 rot, MyVector3 scale, MyVector3 color);
	void RenderObj();

	void AddXModel(char *name);
	void DelXModel(int i);
	void ChangeXModel(int i, char *name);
	void UpdateXModelAnim(float fTimeDelta);
	void SetXModelMatrix(int id, MyMatrix4x4& mat);
	void SetXModelScaleMatrix(int id, D3DXMATRIX& mat);
	void RenderXModelAnim();
	int getXModelNum() {
		return m_vecXModelAnim.size();
	}
private:
	void OneTimeInit();
private:
	D3DCOLOR m_Color;
	LPDIRECT3D9 m_Direct3D;
	LPDIRECT3DDEVICE9 m_Device;
	bool m_renderingScene;

	D3DXMATRIX m_projection;

	LPD3DXFONT *m_fonts;

	MyXModelAnim *m_xModelAnim;
	std::vector<MyXModelAnim *> m_vecXModelAnim;

	myD3DStaticBuffer *m_staticBufferList;
	int m_numStaticBuffers;
	int m_activeStaticBuffer;

	int m_numXModels;

	myD3DTexture *m_textureList;
	unsigned int m_numTextures;

	MyParticleClass *m_particle;

	MySkyBox *m_skyBox;

	MyTerrain *m_terrain;
	int m_screenWidth;
	int m_screenHeight;
	bool m_fullscreen;

	int m_totalFonts;

	MyGUISystem *m_guiList;
	int m_totalGUIs;

	WinHWND m_mainHandle;
	MyLogSystem *m_engineLog;

	MyParticleSystem *m_parSystem;
	int parType;
	float m_near;
	float m_far;

	std::vector<ID3DXMesh *> m_objects;
	std::vector<D3DXMATRIX> m_trans;
	std::vector<D3DMATERIAL9> m_mtrls;
};
//创建渲染引擎对象
bool CreateD3DRender(MyD3DRender **pObj);

