#include "XModel.h"

XFileModelClass::XFileModelClass(IDirect3DDevice9* pd3dDevice)
{
	m_pd3dDevice = pd3dDevice;
}

HRESULT XFileModelClass::LoadModelFromXFile(char* strFilename)
{

	LPD3DXBUFFER pAdjacencyBuffer = NULL;  //����ģ���ڽ���Ϣ
	LPD3DXBUFFER pD3DXMtrlBuffer = NULL;   //�洢����ģ�Ͳ��ʵĻ������

										   //�Ӵ����ļ���������ģ��
	D3DXLoadMeshFromX(strFilename, D3DXMESH_MANAGED, m_pd3dDevice, &pAdjacencyBuffer,
		&pD3DXMtrlBuffer, NULL, &m_dwNumMaterials, &m_pMesh);

	// ��ȡ���ʺ���������
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	m_pMaterials = new D3DMATERIAL9[m_dwNumMaterials];
	m_pTextures = new LPDIRECT3DTEXTURE9[m_dwNumMaterials];

	//���Ӽ���ȡ�������Ժ������ļ���
	for (DWORD i = 0; i<m_dwNumMaterials; i++)
	{
		//��ȡ���ʣ�������һ�»��������ɫֵ
		m_pMaterials[i] = d3dxMaterials[i].MatD3D;
		m_pMaterials[i].Ambient = m_pMaterials[i].Diffuse;

		//����һ���������
		m_pTextures[i] = NULL;
		if (d3dxMaterials[i].pTextureFilename != NULL &&
			strlen(d3dxMaterials[i].pTextureFilename) > 0)
		{
			//��������
			if (FAILED(D3DXCreateTextureFromFileA(m_pd3dDevice, d3dxMaterials[i].pTextureFilename, &m_pTextures[i])))
			{
				MessageBox(NULL, "û���ҵ������ļ�!", "XFileModelClass���ȡ�ļ�����", MB_OK);
			}
		}
	}
	//�Ż�����ģ��
	m_pMesh->OptimizeInplace(D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_STRIPREORDER,
		(DWORD*)pAdjacencyBuffer->GetBufferPointer(), NULL, NULL, NULL);

	return S_OK;
}

HRESULT XFileModelClass::RenderModel()
{
	for (DWORD i = 0; i<m_dwNumMaterials; i++)
	{

		m_pd3dDevice->SetMaterial(&m_pMaterials[i]);
		m_pd3dDevice->SetTexture(0, m_pTextures[i]);
		m_pMesh->DrawSubset(i);
	}
	return S_OK;
}

XFileModelClass::~XFileModelClass(void)
{
	//�ͷ�����ģ�Ͳ���
	SAFE_DELETE_ARRAY(m_pMaterials);

	//�ͷ�����ģ������
	if (m_pTextures)
	{
		for (DWORD i = 0; i < m_dwNumMaterials; i++)
		{
			SAFE_RELEASE(m_pTextures[i]);
		}
		SAFE_DELETE_ARRAY(m_pTextures);
	}

	//�ͷ�����ģ�Ͷ���
	SAFE_RELEASE(m_pMesh);
}

//Ϊ�������������Ƶ��ַ��������ڴ�
HRESULT AllocateName(LPCSTR Name, LPSTR* pNewName)
{
	UINT cbLength;

	if (Name != NULL)
	{
		cbLength = (UINT)strlen(Name) + 1;
		*pNewName = new CHAR[cbLength];
		memcpy(*pNewName, Name, cbLength * sizeof(CHAR));
	}
	else
	{
		*pNewName = NULL;
	}

	return S_OK;
}

//������Ƥ����ģ��
HRESULT GenerateSkinnedMesh(IDirect3DDevice9* pd3dDevice, D3DXMESHCONTAINER_DERIVED* pMeshContainer)
{
	D3DCAPS9 d3dCaps;
	pd3dDevice->GetDeviceCaps(&d3dCaps);

	if (pMeshContainer->pSkinInfo == NULL)
		return S_OK;

	SAFE_RELEASE(pMeshContainer->MeshData.pMesh);
	SAFE_RELEASE(pMeshContainer->pBoneCombinationBuf);


	if (FAILED(pMeshContainer->pSkinInfo->ConvertToBlendedMesh(
		pMeshContainer->pOrigMesh,
		D3DXMESH_MANAGED | D3DXMESHOPT_VERTEXCACHE,
		pMeshContainer->pAdjacency,
		NULL, NULL, NULL,
		&pMeshContainer->NumInfl,
		&pMeshContainer->NumAttributeGroups,
		&pMeshContainer->pBoneCombinationBuf,
		&pMeshContainer->MeshData.pMesh)))
		return E_FAIL;
	return S_OK;
}

//�����ڴ�ͳ�ʼ��
HRESULT CAllocateHierarchy::CreateFrame(LPCSTR Name, LPD3DXFRAME* ppNewFrame)
{
	HRESULT hr = S_OK;
	D3DXFRAME_DERIVED *pFrame;

	*ppNewFrame = NULL;

	// Ϊ���ָ������
	pFrame = new D3DXFRAME_DERIVED;  // ������ܽṹ����
	if (FAILED(AllocateName(Name, (LPSTR*)&pFrame->Name)))
	{
		delete pFrame;
		return hr;
	}

	// ��ʼ��D3DXFRAME_DERIVED�ṹ������Ա����
	D3DXMatrixIdentity(&pFrame->TransformationMatrix);
	D3DXMatrixIdentity(&pFrame->CombinedTransformationMatrix);

	pFrame->pMeshContainer = NULL;
	pFrame->pFrameSibling = NULL;
	pFrame->pFrameFirstChild = NULL;

	*ppNewFrame = pFrame;
	pFrame = NULL;

	return hr;
}

//������Ƥ�����������Լ�����Ƥ��Ϣ
HRESULT CAllocateHierarchy::CreateMeshContainer(LPCSTR Name,
	CONST D3DXMESHDATA *pMeshData,
	CONST D3DXMATERIAL *pMaterials,
	CONST D3DXEFFECTINSTANCE *pEffectInstances,
	DWORD NumMaterials,
	CONST DWORD *pAdjacency,
	LPD3DXSKININFO pSkinInfo,
	LPD3DXMESHCONTAINER *ppNewMeshContainer)
{
	HRESULT hr;
	UINT NumFaces;
	UINT iMaterial;
	UINT iBone, cBones;
	LPDIRECT3DDEVICE9 pd3dDevice = NULL;
	D3DXMESHCONTAINER_DERIVED *pMeshContainer = NULL;

	LPD3DXMESH pMesh = NULL;

	*ppNewMeshContainer = NULL;

	if (pMeshData->Type != D3DXMESHTYPE_MESH)
	{
		hr = E_FAIL;
		goto e_Exit;
	}

	pMesh = pMeshData->pMesh;

	if (pMesh->GetFVF() == 0)
	{
		hr = E_FAIL;
		goto e_Exit;
	}

	pMeshContainer = new D3DXMESHCONTAINER_DERIVED;
	memset(pMeshContainer, 0, sizeof(D3DXMESHCONTAINER_DERIVED));

	hr = AllocateName(Name, &pMeshContainer->Name);
	if (FAILED(hr))
		goto e_Exit;

	pMesh->GetDevice(&pd3dDevice);
	NumFaces = pMesh->GetNumFaces();

	if (!(pMesh->GetFVF() & D3DFVF_NORMAL))
	{
		pMeshContainer->MeshData.Type = D3DXMESHTYPE_MESH;

		hr = pMesh->CloneMeshFVF(pMesh->GetOptions(), pMesh->GetFVF() | D3DFVF_NORMAL,
			pd3dDevice, &pMeshContainer->MeshData.pMesh);
		if (FAILED(hr))
			goto e_Exit;

		pMesh = pMeshContainer->MeshData.pMesh;

		D3DXComputeNormals(pMesh, NULL);
	}
	else  
	{
		pMeshContainer->MeshData.pMesh = pMesh;
		pMeshContainer->MeshData.Type = D3DXMESHTYPE_MESH;

		pMesh->AddRef();
	}

	pMeshContainer->NumMaterials = max(1, NumMaterials);
	pMeshContainer->pMaterials = new D3DXMATERIAL[pMeshContainer->NumMaterials];
	pMeshContainer->ppTextures = new LPDIRECT3DTEXTURE9[pMeshContainer->NumMaterials];
	pMeshContainer->pAdjacency = new DWORD[NumFaces * 3];

	memcpy(pMeshContainer->pAdjacency, pAdjacency, sizeof(DWORD) * NumFaces * 3);
	memset(pMeshContainer->ppTextures, 0, sizeof(LPDIRECT3DTEXTURE9) * pMeshContainer->NumMaterials);

	if (NumMaterials > 0)
	{
		memcpy(pMeshContainer->pMaterials, pMaterials, sizeof(D3DXMATERIAL) * NumMaterials);

		for (iMaterial = 0; iMaterial < NumMaterials; iMaterial++)
		{
			if (pMeshContainer->pMaterials[iMaterial].pTextureFilename != NULL)
			{
				if (FAILED(D3DXCreateTextureFromFileA(pd3dDevice, pMeshContainer->pMaterials[iMaterial].pTextureFilename,
					&pMeshContainer->ppTextures[iMaterial])))
					pMeshContainer->ppTextures[iMaterial] = NULL;

				pMeshContainer->pMaterials[iMaterial].pTextureFilename = NULL;
			}
		}
	}
	else
	{
		pMeshContainer->pMaterials[0].pTextureFilename = NULL;
		memset(&pMeshContainer->pMaterials[0].MatD3D, 0, sizeof(D3DMATERIAL9));
		pMeshContainer->pMaterials[0].MatD3D.Diffuse.r = 0.5f;
		pMeshContainer->pMaterials[0].MatD3D.Diffuse.g = 0.5f;
		pMeshContainer->pMaterials[0].MatD3D.Diffuse.b = 0.5f;
		pMeshContainer->pMaterials[0].MatD3D.Specular = pMeshContainer->pMaterials[0].MatD3D.Diffuse;
	}

	if (pSkinInfo != NULL)
	{
		pMeshContainer->pSkinInfo = pSkinInfo;
		pSkinInfo->AddRef();

		pMeshContainer->pOrigMesh = pMesh;
		pMesh->AddRef();

		cBones = pSkinInfo->GetNumBones();
		pMeshContainer->pBoneOffsetMatrices = new D3DXMATRIX[cBones];

		for (iBone = 0; iBone < cBones; iBone++)
		{
			pMeshContainer->pBoneOffsetMatrices[iBone] = *(pMeshContainer->pSkinInfo->GetBoneOffsetMatrix(iBone));
		}

		hr = GenerateSkinnedMesh(pd3dDevice, pMeshContainer);
		if (FAILED(hr))
			goto e_Exit;
	}

	*ppNewMeshContainer = pMeshContainer;
	pMeshContainer = NULL;

e_Exit:
	SAFE_RELEASE(pd3dDevice);

	if (pMeshContainer != NULL)
	{
		DestroyMeshContainer(pMeshContainer);
	}

	return hr;
}

//�ͷŹ������
HRESULT CAllocateHierarchy::DestroyFrame(LPD3DXFRAME pFrameToFree)
{
	SAFE_DELETE_ARRAY(pFrameToFree->Name);
	SAFE_DELETE(pFrameToFree);
	return S_OK;
}

//�ͷ���������
HRESULT CAllocateHierarchy::DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase)
{
	UINT iMaterial;
	D3DXMESHCONTAINER_DERIVED* pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)pMeshContainerBase;

	SAFE_DELETE_ARRAY(pMeshContainer->Name);
	SAFE_DELETE_ARRAY(pMeshContainer->pAdjacency);
	SAFE_DELETE_ARRAY(pMeshContainer->pMaterials);
	SAFE_DELETE_ARRAY(pMeshContainer->pBoneOffsetMatrices);

	if (pMeshContainer->ppTextures != NULL)
	{
		for (iMaterial = 0; iMaterial < pMeshContainer->NumMaterials; iMaterial++)
		{
			SAFE_RELEASE(pMeshContainer->ppTextures[iMaterial]);
		}
	}

	SAFE_DELETE_ARRAY(pMeshContainer->ppTextures);
	SAFE_DELETE_ARRAY(pMeshContainer->ppBoneMatrixPtrs);
	SAFE_RELEASE(pMeshContainer->pBoneCombinationBuf);
	SAFE_RELEASE(pMeshContainer->MeshData.pMesh);
	SAFE_RELEASE(pMeshContainer->pSkinInfo);
	SAFE_RELEASE(pMeshContainer->pOrigMesh);
	SAFE_DELETE(pMeshContainer);
	return S_OK;
}

//���úø�����ܵ���ϱ任����
HRESULT MyXModelAnim::SetupBoneMatrixPointers(LPD3DXFRAME pFrameBase, LPD3DXFRAME pFrameRoot)
{
	if (pFrameBase->pMeshContainer != NULL)
	{
		D3DXFRAME_DERIVED* pFrame = NULL;
		D3DXMESHCONTAINER_DERIVED* pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)pFrameBase->pMeshContainer;

		if (pMeshContainer->pSkinInfo != NULL)
		{
			UINT cBones = pMeshContainer->pSkinInfo->GetNumBones();
			pMeshContainer->ppBoneMatrixPtrs = new D3DXMATRIX*[cBones];
			for (UINT iBone = 0; iBone < cBones; iBone++)
			{
				pFrame = (D3DXFRAME_DERIVED*)D3DXFrameFind(pFrameRoot, pMeshContainer->pSkinInfo->GetBoneName(iBone));
				if (pFrame == NULL) return E_FAIL;

				pMeshContainer->ppBoneMatrixPtrs[iBone] = &pFrame->CombinedTransformationMatrix;
			}
		}
	}

	if (pFrameBase->pFrameSibling != NULL)
	{
		if (FAILED(SetupBoneMatrixPointers(pFrameBase->pFrameSibling, pFrameRoot)))
			return E_FAIL;
	}

	if (pFrameBase->pFrameFirstChild != NULL)
	{
		if (FAILED(SetupBoneMatrixPointers(pFrameBase->pFrameFirstChild, pFrameRoot)))
			return E_FAIL;
	}

	return S_OK;
}

//������Ƥ�����е���Ƥ����
void MyXModelAnim::DrawMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase, LPD3DXFRAME pFrameBase)
{
	D3DXMESHCONTAINER_DERIVED* pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)pMeshContainerBase;
	D3DXFRAME_DERIVED* pFrame = (D3DXFRAME_DERIVED*)pFrameBase;
	UINT iMaterial;
	UINT NumBlend;
	UINT iAttrib;
	DWORD AttribIdPrev;
	LPD3DXBONECOMBINATION pBoneComb;

	UINT iMatrixIndex;
	D3DXMATRIXA16 matTemp;
	D3DCAPS9 d3dCaps;
	m_d3dDevice->GetDeviceCaps(&d3dCaps);

	if (pMeshContainer->pSkinInfo != NULL)
	{
		AttribIdPrev = UNUSED32;
		pBoneComb = reinterpret_cast<LPD3DXBONECOMBINATION>(pMeshContainer->pBoneCombinationBuf->GetBufferPointer());

		for (iAttrib = 0; iAttrib < pMeshContainer->NumAttributeGroups; iAttrib++)
		{
			NumBlend = 0;
			for (DWORD i = 0; i < pMeshContainer->NumInfl; ++i)
			{
				if (pBoneComb[iAttrib].BoneId[i] != UINT_MAX)
				{
					NumBlend = i;
				}
			}

			if (d3dCaps.MaxVertexBlendMatrices >= NumBlend + 1)
			{
				for (DWORD i = 0; i < pMeshContainer->NumInfl; ++i)
				{
					iMatrixIndex = pBoneComb[iAttrib].BoneId[i];
					if (iMatrixIndex != UINT_MAX)
					{
						D3DXMatrixMultiply(&matTemp, &pMeshContainer->pBoneOffsetMatrices[iMatrixIndex],
							pMeshContainer->ppBoneMatrixPtrs[iMatrixIndex]);
						m_d3dDevice->SetTransform(D3DTS_WORLDMATRIX(i), &matTemp);
					}
				}

				m_d3dDevice->SetRenderState(D3DRS_VERTEXBLEND, NumBlend);

				if ((AttribIdPrev != pBoneComb[iAttrib].AttribId) || (AttribIdPrev == UNUSED32))
				{
					m_d3dDevice->SetMaterial(&pMeshContainer->pMaterials[pBoneComb[iAttrib].AttribId].MatD3D);
					m_d3dDevice->SetTexture(0, pMeshContainer->ppTextures[pBoneComb[iAttrib].AttribId]);
					AttribIdPrev = pBoneComb[iAttrib].AttribId;
				}

				pMeshContainer->MeshData.pMesh->DrawSubset(iAttrib);
			}
		}
		m_d3dDevice->SetRenderState(D3DRS_VERTEXBLEND, 0);
	}
	else
	{
		m_d3dDevice->SetTransform(D3DTS_WORLD, &pFrame->CombinedTransformationMatrix);

		for (iMaterial = 0; iMaterial < pMeshContainer->NumMaterials; iMaterial++)
		{
			m_d3dDevice->SetMaterial(&pMeshContainer->pMaterials[iMaterial].MatD3D);
			m_d3dDevice->SetTexture(0, pMeshContainer->ppTextures[iMaterial]);
			pMeshContainer->MeshData.pMesh->DrawSubset(iMaterial);
		}
	}
}

//���ƹ���
void MyXModelAnim::DrawFrame(LPD3DXFRAME pFrame)
{
	if (pFrame == NULL) return;
	LPD3DXMESHCONTAINER pMeshContainer;
	pMeshContainer = pFrame->pMeshContainer;  // ȡ����������
	while (pMeshContainer != NULL)
	{
		DrawMeshContainer(pMeshContainer, pFrame);  // ���Ʒǿ���Ƥ����
		pMeshContainer = pMeshContainer->pNextMeshContainer;    // ����������������
	}

	DrawFrame(pFrame->pFrameSibling);  // �����ֵܿ��
	DrawFrame(pFrame->pFrameFirstChild);  // �����ӿ��
}

//���±任����
void MyXModelAnim::UpdateFrameMatrices(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix)
{
	if (pFrameBase == NULL || pParentMatrix == NULL) return;
	D3DXFRAME_DERIVED* pFrame = (D3DXFRAME_DERIVED*)pFrameBase;

	// ����ǰ����������ڸ�������ƫ�ƾ������ۻ�����
	D3DXMatrixMultiply(&pFrame->CombinedTransformationMatrix, &pFrame->TransformationMatrix, pParentMatrix);

	UpdateFrameMatrices(pFrame->pFrameSibling, pParentMatrix);                              // �����ֵܹ���
	UpdateFrameMatrices(pFrame->pFrameFirstChild, &pFrame->CombinedTransformationMatrix);   // �����ӹ���
}

MyXModelAnim::MyXModelAnim(IDirect3DDevice9* pd3dDevice) {
	m_d3dDevice = pd3dDevice;
	m_pFrameRoot = 0;
	m_pBoneMatrices = 0;
	m_pAllocateHier = 0;
	m_pAnimController = 0;
}

MyXModelAnim::~MyXModelAnim() {

}

void MyXModelAnim::InitXModel(char *name) {
	m_pAllocateHier = new CAllocateHierarchy();
	D3DXLoadMeshHierarchyFromX(name, D3DXMESH_MANAGED, m_d3dDevice,
		m_pAllocateHier, NULL, &m_pFrameRoot, &m_pAnimController);
	SetupBoneMatrixPointers(m_pFrameRoot, m_pFrameRoot);
}

void MyXModelAnim::UpdateXModel(float fTimeDelta) {
	// ���ù��������ľ���
	D3DXMATRIX matFinal;
	//D3DXMATRIX  matScal;
	D3DXMatrixIdentity(&matFinal);
	//D3DXMatrixScaling(&matScal, 1.0f, 1.0f, 1.0f);
	matFinal = m_scaleMat *matFinal * (*(D3DXMATRIX*)(&m_worldMat)->matrix);
	m_d3dDevice->SetTransform(D3DTS_WORLD, &matFinal);

	// ���¹�������
	m_pAnimController->AdvanceTime(fTimeDelta, NULL);  //���ù���������ʱ��
	UpdateFrameMatrices(m_pFrameRoot, &matFinal);   //���¿���еı任����
}

void MyXModelAnim::RenderXModel() {
	DrawFrame(m_pFrameRoot);
}
