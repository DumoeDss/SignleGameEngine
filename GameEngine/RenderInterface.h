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
	//��ʼ��
	virtual bool Initialize(int w, int h, WinHWND mainWin, bool fullScreen, UGP_MS_TYPE ms) = 0;	
	virtual void OneTimeInit() = 0;
	//�ͷ���Դ
	virtual void Shutdown() = 0;
	//����
	virtual void SetClearCol(float r, float g, float b) = 0;
	//��ʼ��Ⱦ
	virtual void StartRender(bool bColor, bool bDepth, bool bStencil) = 0;
	//������Ⱦ
	virtual void EndRendering() = 0;
	//�������
	virtual void ClearBuffers(bool bColor, bool bDepth, bool bStencil) = 0;
	//������̬����
	virtual int CreateStaticBuffer(VertexType, PrimType, 
		int totalVerts, int totalIndices,
		int stride, void **data, unsigned int *indices, int *staticId) = 0;
	//���ò���
	virtual void SetMaterial(myMaterial *mat) = 0;
	//���ù�Դ
	virtual void SetLight(myLight *light, int index) = 0;
	//�رչ�Դ
	virtual void DisabledLight(int index) = 0;

	virtual void SetTranspency(RenderState state, TransState src, TransState dst) = 0;
	//����Ч
	virtual void EnableFog(float start, float end, UGP_FOG_TYPE type, 
		unsigned long color, bool rangeFog) = 0;
	//�ر���Ч
	virtual void DisableFog() = 0;
	//�����ͼ
	virtual int AddTexture2D(char *file, int *texId) = 0;
	virtual void SetTextureFilter(int index, int filter, int val) = 0;
	//
	virtual void SetMultiTexture() = 0;
	virtual void SetDetailMapping() = 0;
	virtual void ApplyTexture(int index, int texId) = 0;
	virtual void SaveScreenShot(char *file) = 0;
	virtual void EnablePointSprites(float size, float min, float a, float b, float c) = 0;
	virtual void DisablePointSprites() = 0;
	//�����ı�
	virtual bool CreateText(char *font, int weight, bool italic, int size, int &id) = 0;
	//��ʾ�ı�
	virtual void DisplayText(int id, long x, long y, int r, int g, int b, char *text, ...) = 0;
	virtual void DisplayText(int id, long x, long y, unsigned long color, char *text, ...) = 0;
	//����GUI
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
	//�ͷ�GUI����
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
	//��ӱ���
	virtual bool AddGUIBackdrop(int guiId, char *fileName) = 0;
	//��Ӿ�̬�ı�
	virtual bool AddGUIStaticText(int guiId, int id,
		char *text, int x, int y, unsigned long color,
		int fontID) = 0;
	//��Ӱ�ť
	virtual bool AddGUIButton(int guiId, int id, int x, int y,
		char *up, char *over, char *down) = 0;
	//��ȾGUI
	virtual void ProcessGUI(int guiID, bool LMBDown,
		int mouseX, int mouseY,
		void(*funcPtr)(int id, int state)) = 0;

	//����ͶӰ����
	virtual void CalculateProjMatrix(float fov,float n, float f) = 0;
	virtual void CalculateOrthoMatrix(float n, float f) = 0;
	//����ģ��
	virtual int LoadXModel(char *file, int *xModelId) = 0;
	virtual int LoadXModel(char *file, int xModelId) = 0;
	//�ͷŻ������
	virtual void ReleaseAllStaticBuffers() = 0;	
	virtual int ReleaseStaticBuffer(int staticID) = 0;
	//�ͷ�ģ�Ͷ���
	virtual void ReleaseAllXModels() = 0;
	virtual int ReleaseXModel(int xModelId) = 0;
	//��Ⱦģ��
	virtual int RenderXModel(int xModelId) = 0;
	//��Ⱦ��̬����
	virtual int RenderStaticBuffer(int staticId) = 0;
	//��ȡģ�ͱ߽���
	virtual void GetXModelBoundingSphere(int xModelId, MyVector3 *origin, float *radius) = 0;
	//ģ�Ͷ���
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
