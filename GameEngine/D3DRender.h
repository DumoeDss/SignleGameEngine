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
	//��ʼ����Ⱦ�������
	bool InitRender(int w, int h, WinHWND mainWin, bool fullScreen, MultiSampleType ms);
	//����
	void SetClearCol(float r, float g, float b);
	//�ͷ���Դ
	void Shutdown();
	//��ʼ��Ⱦ
	void StartRender(bool bColor, bool bDepth, bool bStencil);
	//������Ⱦ
	void EndRendering();
	//�������
	void ClearBuffers(bool bColor, bool bDepth, bool bStencil);
	//������̬����
	int CreateStaticBuffer(VertexType, PrimType, 
		int totalVerts, int totalIndices,
		int stride, void **data, unsigned int *indices, int *staticId);
	//���ò���
	void SetMaterial(myMaterial *mat);
	//���ù�Դ
	void SetLight(myLight *light, int index);
	//�رչ�Դ
	void DisabledLight(int index);
	//����͸����
	void SetTranspency(RenderState state, TransState src, TransState dst);
	//����Ч
	void EnableFog(float start, float end, FogType type, 
		unsigned long color, bool rangeFog);
	//�ر���Ч
	void DisableFog();
	//���������ͼ
	int AddTexture2D(char *file, int *texId);
	//�������������
	void SetTextureFilter(int index, int filter, int val);
	//���ö�������
	void SetMultiTexture();
	void SetDetailMapping();
	//Ӧ��������ͼ
	void ApplyTexture(int index, int texId);
	//����
	void SaveScreenShot(char *file);
	//����㾫��
	void EnablePointSprites(float size, float min, float a, float b, float c);
	//�رյ㾫��
	void DisablePointSprites();
	//�����ı�
	bool CreateText(char *font, int weight, bool italic, int size, int &id);
	//��ʾ�ı�
	void DisplayText(int id, long x, long y, int r, int g, int b, char *text, ...);
	void DisplayText(int id, long x, long y, unsigned long color, char *text, ...);
	//��ӱ���
	bool AddGUIBackdrop(int guiId, char *fileName);
	//��Ӿ�̬�ı�
	bool AddGUIStaticText(int guiId, int id,
		char *text, int x, int y, unsigned long color,
		int fontID);
	//ɾ����ť
	bool DelGUIButton(int guiId, int id);
	//ɾ����̬�ı�
	bool DelGUIStaticText(int guiId, int id);
	//��Ӱ�ť
	bool AddGUIButton(int guiId, int id, int x, int y,
		char *up, char *over, char *down);
	//��ȾGUI
	void ProcessGUI(int guiId, bool LMBDown,
		int mouseX, int mouseY,
		void(*funcPtr)(int id, int state));
	LPDIRECT3DDEVICE9 GetDevice();
	//����ͶӰ����
	void CalculateProjMatrix(float fov,float n, float f);
	void CalculateOrthoMatrix(float n, float f);

	int RenderStaticBuffer(int staticId);
	//��Ⱦģ��
	int RenderXModel(int xModelId);

	//����GUI
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
	//�ͷ�GUI����
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

	//����
	void InitParticle(int type, int length, int width,
		int height,char* fileName,int numParticles,MyVector3 pos);
	bool RenderParticle(float fElapsedTime);

	//��պ�
	bool InitSkyBox(float skyLen, std::vector<char *> skyName);
	bool RenderSkyBox(D3DXMATRIX *pMatWorld, bool bRenderFrame);
	//����
	bool InitTerrain(std::string heightmapFileName,
		int numVertsPerRow,
		int numVertsPerCol,
		int cellSpacing,
		float heightScale,
		std::string textureFileName);
	void RenderTerrain(bool drawTris);
	float getHeight(float x, float z);
	//������ ����
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
//������Ⱦ�������
bool CreateD3DRender(MyD3DRender **pObj);

