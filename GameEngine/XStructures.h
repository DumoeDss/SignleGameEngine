#pragma once

#include<d3d9.h>
#include<d3dx9.h>


struct myD3DFrameEx: public D3DXFRAME
{
   D3DXMATRIX finalMatrix;
};


struct myD3DContainerEx: public D3DXMESHCONTAINER
{
   LPDIRECT3DTEXTURE9 *textures;
   D3DMATERIAL9 *mat;
   LPD3DXMESH originalMesh;
   D3DXMATRIX **boneMatrices;
};


class MyD3DAllocate : public ID3DXAllocateHierarchy
{
   public:	
      STDMETHOD(CreateFrame)(THIS_ LPCSTR name, LPD3DXFRAME *outFrame);

      STDMETHOD(CreateMeshContainer)(THIS_ LPCSTR name, CONST D3DXMESHDATA *mesh, 
         CONST D3DXMATERIAL *mats, CONST D3DXEFFECTINSTANCE *effects,
         DWORD numMats, CONST DWORD *indices, LPD3DXSKININFO skin, 
         LPD3DXMESHCONTAINER *outContainer);

      STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME inFrame);
      STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER container);
};
