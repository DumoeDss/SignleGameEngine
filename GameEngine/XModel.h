#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "Defines.h"
#include "MathLibrary.h"
class XFileModelClass
{
private:
	LPDIRECT3DDEVICE9				m_pd3dDevice;			//D3D设备对象
	LPD3DXMESH						m_pMesh;       //网格模型对象
	DWORD								m_dwNumMaterials; //材质的数量
	D3DMATERIAL9*					m_pMaterials;     //模型材质结构体的实例
	LPDIRECT3DTEXTURE9 *			m_pTextures;      //模型纹理结构体的实例

public:
	XFileModelClass(IDirect3DDevice9 *pd3dDevice); //构造函数
	~XFileModelClass(void);     //析构函数   

public:
	HRESULT		LoadModelFromXFile(char* strFilename);  //从.X文件读取三维模型到内存中
	HRESULT		RenderModel();  //渲染三维网格模型

};



struct D3DXFRAME_DERIVED : public D3DXFRAME
{
	D3DXMATRIXA16 CombinedTransformationMatrix;
};

struct D3DXMESHCONTAINER_DERIVED : public D3DXMESHCONTAINER
{
	LPDIRECT3DTEXTURE9*  ppTextures;            //纹理数组
	LPD3DXMESH           pOrigMesh;             //原始网格
	LPD3DXATTRIBUTERANGE pAttributeTable;
	DWORD                NumAttributeGroups;    //属性组数量,即子网格数量
	DWORD                NumInfl;               //每个顶点最多受多少骨骼的影响
	LPD3DXBUFFER         pBoneCombinationBuf;   //骨骼结合表
	D3DXMATRIX**         ppBoneMatrixPtrs;      //存放骨骼的组合变换矩阵
	D3DXMATRIX*          pBoneOffsetMatrices;   //存放骨骼的初始变换矩阵
	DWORD                NumPaletteEntries;     //骨骼数量上限
	bool                 UseSoftwareVP;         //标识是否使用软件顶点处理
};


//加载框架层次和网格模型数据
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
