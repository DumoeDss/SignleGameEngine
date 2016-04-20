#pragma once

#include "Defines.h"
#include "material.h"
#include "light.h"
#include "GUI.h"
#include "Matrix.h"
#include "Camera.h"

class MyRenderInterface
{
public:
	MyRenderInterface() : m_screenWidth(0),
		m_screenHeight(0), m_near(0), m_far(0) {}
	virtual ~MyRenderInterface(){}
	//初始化
	virtual bool Initialize(int w, int h, WinHWND mainWin, bool fullScreen, UGP_MS_TYPE ms) = 0;	
	virtual void OneTimeInit() = 0;
	//释放资源
	virtual void Shutdown() = 0;
	//清屏
	virtual void SetClearCol(float r, float g, float b) = 0;
	//开始渲染
	virtual void StartRender(bool bColor, bool bDepth, bool bStencil) = 0;
	//结束渲染
	virtual void EndRendering() = 0;
	//清除缓存
	virtual void ClearBuffers(bool bColor, bool bDepth, bool bStencil) = 0;
	//创建静态缓存
	virtual int CreateStaticBuffer(VertexType, PrimType, 
		int totalVerts, int totalIndices,
		int stride, void **data, unsigned int *indices, int *staticId) = 0;
	//设置材质
	virtual void SetMaterial(myMaterial *mat) = 0;
	//设置光源
	virtual void SetLight(myLight *light, int index) = 0;
	//关闭光源
	virtual void DisabledLight(int index) = 0;

	virtual void SetTranspency(RenderState state, TransState src, TransState dst) = 0;
	//打开雾效
	virtual void EnableFog(float start, float end, UGP_FOG_TYPE type, 
		unsigned long color, bool rangeFog) = 0;
	//关闭雾效
	virtual void DisableFog() = 0;
	//添加贴图
	virtual int AddTexture2D(char *file, int *texId) = 0;
	virtual void SetTextureFilter(int index, int filter, int val) = 0;
	//
	virtual void SetMultiTexture() = 0;
	virtual void SetDetailMapping() = 0;
	virtual void ApplyTexture(int index, int texId) = 0;
	virtual void SaveScreenShot(char *file) = 0;
	virtual void EnablePointSprites(float size, float min, float a, float b, float c) = 0;
	virtual void DisablePointSprites() = 0;
	//创建文本
	virtual bool CreateText(char *font, int weight, bool italic, int size, int &id) = 0;
	//显示文本
	virtual void DisplayText(int id, long x, long y, int r, int g, int b, char *text, ...) = 0;
	virtual void DisplayText(int id, long x, long y, unsigned long color, char *text, ...) = 0;
	//创建GUI
	bool CreateGUI(int &id)
	{
		if(!m_guiList)
		{
			m_guiList = new MyGUISystem[1];
			if(!m_guiList) return RE_FAIL;
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
		for(int s=0; s<m_totalGUIs; s++)
		{
			m_guiList[s].Shutdown();
		}
		m_totalGUIs = 0;
		if(m_guiList) delete[] m_guiList;
		m_guiList = NULL;
	}
	//添加背景
	virtual bool AddGUIBackdrop(int guiId, char *fileName) = 0;
	//添加静态文本
	virtual bool AddGUIStaticText(int guiId, int id,
		char *text, int x, int y, unsigned long color,
		int fontID) = 0;
	//添加按钮
	virtual bool AddGUIButton(int guiId, int id, int x, int y,
		char *up, char *over, char *down) = 0;
	//渲染GUI
	virtual void ProcessGUI(int guiID, bool LMBDown,
		int mouseX, int mouseY,
		void(*funcPtr)(int id, int state)) = 0;

	//计算投影矩阵
	virtual void CalculateProjMatrix(float fov,float n, float f) = 0;
	virtual void CalculateOrthoMatrix(float n, float f) = 0;
	//加载模型
	virtual int LoadXModel(char *file, int *xModelId) = 0;
	virtual int LoadXModel(char *file, int xModelId) = 0;
	//释放缓存对象
	virtual void ReleaseAllStaticBuffers() = 0;	
	virtual int ReleaseStaticBuffer(int staticID) = 0;
	//释放模型对象
	virtual void ReleaseAllXModels() = 0;
	virtual int ReleaseXModel(int xModelId) = 0;
	//渲染模型
	virtual int RenderXModel(int xModelId) = 0;
	//渲染静态缓存
	virtual int RenderStaticBuffer(int staticId) = 0;
	//获取模型边界球
	virtual void GetXModelBoundingSphere(int xModelId, MyVector3 *origin, float *radius) = 0;
	//模型动画
	virtual void UpdateXAnimation(int xModelId, float time, MyMatrix4x4 *mat) = 0;

	virtual void ApplyView(MyVector3 pos, MyVector3 view, MyVector3 up) = 0;
	virtual void SetWorldMatrix(MyMatrix4x4 *mat) = 0;
	virtual void CameraToViewMatrix(MyCamera *cam, MyMatrix4x4 *mat) = 0;
	virtual void GetProjectMatrix(MyMatrix4x4 *mat) = 0;

	virtual bool InitSkyBox(float Length) = 0;
	virtual bool LoadSkyTextureFromFile(char *pFrontTextureFile, char *pBackTextureFile, char *pLeftTextureFile, char *pRightTextureFile, char *pTopTextureFile) = 0;
	virtual void RenderSkyBox(D3DXMATRIX *pMatWorld, bool bRenderFrame) = 0;
protected:
	int m_screenWidth;
	int m_screenHeight;
	bool m_fullscreen;

	int m_totalFonts;

	MyGUISystem *m_guiList;
	int m_totalGUIs;

	WinHWND m_mainHandle;

	float m_near;
	float m_far;
};
