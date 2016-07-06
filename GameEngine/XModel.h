#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "Defines.h"
#include "MathLibrary.h"
class XFileModelClass
{
private:
	LPDIRECT3DDEVICE9				m_pd3dDevice;			//D3D�豸����
	LPD3DXMESH						m_pMesh;       //����ģ�Ͷ���
	DWORD								m_dwNumMaterials; //���ʵ�����
	D3DMATERIAL9*					m_pMaterials;     //ģ�Ͳ��ʽṹ���ʵ��
	LPDIRECT3DTEXTURE9 *			m_pTextures;      //ģ������ṹ���ʵ��

public:
	XFileModelClass(IDirect3DDevice9 *pd3dDevice); //���캯��
	~XFileModelClass(void);     //��������   

public:
	HRESULT		LoadModelFromXFile(char* strFilename);  //��.X�ļ���ȡ��άģ�͵��ڴ���
	HRESULT		RenderModel();  //��Ⱦ��ά����ģ��

};



struct D3DXFRAME_DERIVED : public D3DXFRAME
{
	D3DXMATRIXA16 CombinedTransformationMatrix;
};

struct D3DXMESHCONTAINER_DERIVED : public D3DXMESHCONTAINER
{
	LPDIRECT3DTEXTURE9*  ppTextures;            //��������
	LPD3DXMESH           pOrigMesh;             //ԭʼ����
	LPD3DXATTRIBUTERANGE pAttributeTable;
	DWORD                NumAttributeGroups;    //����������,������������
	DWORD                NumInfl;               //ÿ����������ܶ��ٹ�����Ӱ��
	LPD3DXBUFFER         pBoneCombinationBuf;   //������ϱ�
	D3DXMATRIX**         ppBoneMatrixPtrs;      //��Ź�������ϱ任����
	D3DXMATRIX*          pBoneOffsetMatrices;   //��Ź����ĳ�ʼ�任����
	DWORD                NumPaletteEntries;     //������������
	bool                 UseSoftwareVP;         //��ʶ�Ƿ�ʹ��������㴦��
};


//���ؿ�ܲ�κ�����ģ������
class CAllocateHierarchy : public ID3DXAllocateHierarchy
{
public:
	STDMETHOD(CreateFrame)(THIS_ LPCSTR Name, LPD3DXFRAME *ppNewFrame);
	STDMETHOD(CreateMeshContainer)(THIS_ LPCSTR              Name,
		CONST D3DXMESHDATA*       pMeshData,
		CONST D3DXMATERIAL*       pMaterials,
		CONST D3DXEFFECTINSTANCE* pEffectInstances,
		DWORD                     NumMaterials,
		CONST DWORD *             pAdjacency,
		LPD3DXSKININFO pSkinInfo,
		LPD3DXMESHCONTAINER *ppNewMeshContainer);
	STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME pFrameToFree);
	STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER pMeshContainerBase);
};

class MyXModelAnim {
public:
	MyXModelAnim(IDirect3DDevice9* pd3dDevice);
	~MyXModelAnim();
	void DrawFrame(LPD3DXFRAME pFrame);
	void DrawMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase, LPD3DXFRAME pFrameBase);
	HRESULT SetupBoneMatrixPointers(LPD3DXFRAME pFrameBase, LPD3DXFRAME pFrameRoot);
	void UpdateFrameMatrices(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix);
	void InitXModel(char *name);
	void UpdateXModel(float fTimeDelta);
	void RenderXModel();
	void SetMatrix(MyMatrix4x4 &Mat) {
		m_worldMat = Mat;
	}
	const MyMatrix4x4 GetMatrix() {
		return m_worldMat;
	}
	void SetScaleMatrix(D3DXMATRIX& mat) {
		m_scaleMat = mat;
	}
private:
	IDirect3DDevice9* m_d3dDevice;
	LPD3DXFRAME m_pFrameRoot;
	D3DXMATRIX* m_pBoneMatrices;
	CAllocateHierarchy* m_pAllocateHier;
	LPD3DXANIMATIONCONTROLLER m_pAnimController;
	MyMatrix4x4 m_worldMat;
	D3DXMATRIX m_scaleMat;
};
