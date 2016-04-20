#include <stdio.h>
#include "D3DRender.h"

inline unsigned long FtoDW(float v)
{
	return *((unsigned long *)&v);
}

#define D3DFVF_GUI (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define D3DFVF_MV (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

bool CreateD3DRenderer(MyRenderInterface **pObj)
{
	if(!*pObj) 
		*pObj = new MyD3DRenderer();
	else
		return false;

	return true;
}

unsigned long CreateD3DFVF(int flags)
{
	unsigned long fvf = 0;

	if(flags == MY_FVF_GUI) fvf = D3DFVF_GUI;
	if(flags == MY_FVF_MV) fvf = D3DFVF_MV;

	return fvf;
}

D3DMULTISAMPLE_TYPE GetD3DMultiSampleType(LPDIRECT3D9 d3d,
	UGP_MS_TYPE ms, D3DDEVTYPE type, D3DFORMAT format, bool fullscreen)
{
	D3DMULTISAMPLE_TYPE t = D3DMULTISAMPLE_NONE;

	if(d3d)
	{
		switch(ms)
		{
		case D3DMULTISAMPLE_NONE:
			t = D3DMULTISAMPLE_NONE;
			break;
		case UGP_MS_SAMPLES_2:
			if(d3d->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT,
				type,format,!fullscreen,D3DMULTISAMPLE_2_SAMPLES,
				NULL) == D3D_OK) t = D3DMULTISAMPLE_2_SAMPLES;
			break;
		case UGP_MS_SAMPLES_4:
			if(d3d->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT,
				type,format,!fullscreen,D3DMULTISAMPLE_4_SAMPLES,
				NULL) == D3D_OK) t = D3DMULTISAMPLE_4_SAMPLES;
			break;
		case UGP_MS_SAMPLES_8:
			if(d3d->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT,
				type,format,!fullscreen,D3DMULTISAMPLE_8_SAMPLES,
				NULL) == D3D_OK) t = D3DMULTISAMPLE_8_SAMPLES;
			break;
		case UGP_MS_SAMPLES_16:
			if(d3d->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT,
				type,format,!fullscreen,D3DMULTISAMPLE_16_SAMPLES,
				NULL) == D3D_OK) t = D3DMULTISAMPLE_16_SAMPLES;
			break;
		default:
			break;
		}
	}
	return t;
}

MyD3DRenderer::MyD3DRenderer()
{
	m_Direct3D = NULL;
	m_Device = NULL;
	m_renderingScene = false;
	m_numStaticBuffers = 0;
	m_activeStaticBuffer = RE_INVALID;
	m_staticBufferList = NULL;

	m_textureList = NULL;
	m_numTextures = 0;
	m_totalFonts = 0;
	m_guiList = NULL;
	m_totalGUIs = 0;
	m_fonts = NULL;
	m_xModels = NULL;
	m_numXModels = 0;
}

MyD3DRenderer::~MyD3DRenderer()
{
	Shutdown();
}

bool MyD3DRenderer::Initialize(int w, int h, WinHWND mainWin, 
	bool fullScreen, UGP_MS_TYPE ms)
{
	Shutdown();

	m_mainHandle = mainWin;
	if(!m_mainHandle) return false;

	m_fullscreen = fullScreen;

	D3DDISPLAYMODE mode;
	D3DCAPS9 caps;
	D3DPRESENT_PARAMETERS Params;

	ZeroMemory(&Params, sizeof(Params));

	m_Direct3D = Direct3DCreate9(D3D_SDK_VERSION);
	if(!m_Direct3D) return false;

	if(FAILED(m_Direct3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&mode))) return false;

	if(FAILED(m_Direct3D->GetDeviceCaps(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,&caps))) return false;

	DWORD processing = 0;
	if(caps.VertexProcessingCaps != 0)
		processing = D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE;
	else
		processing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	if(m_fullscreen)
	{
		Params.FullScreen_RefreshRateInHz = mode.RefreshRate;
		Params.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	}
	else
		Params.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	Params.Windowed = !m_fullscreen;
	Params.BackBufferWidth = w;
	Params.BackBufferHeight = h;
	Params.hDeviceWindow = m_mainHandle;
	Params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	Params.BackBufferFormat = mode.Format;
	Params.BackBufferCount = 1;
	Params.EnableAutoDepthStencil = TRUE;
	Params.AutoDepthStencilFormat = D3DFMT_D16;
	Params.MultiSampleType = GetD3DMultiSampleType(m_Direct3D,ms,D3DDEVTYPE_HAL,mode.Format,m_fullscreen);
	m_screenWidth = w;
	m_screenHeight = h;

	if(FAILED(m_Direct3D->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,m_mainHandle,processing,&Params,&m_Device))) return false;
	if(m_Device == NULL) return false;

	OneTimeInit();

	return true;
}

void MyD3DRenderer::OneTimeInit()
{
	if(!m_Device) return;

	m_Device->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	CalculateProjMatrix(D3DX_PI/4, 0.1f, 1000);
}

void MyD3DRenderer::CalculateProjMatrix(float fov,float n, float f)
{
	if(!m_Device) return;
	D3DXMATRIX projection;

	D3DXMatrixPerspectiveFovLH(&projection, fov, (float)m_screenWidth/(float)m_screenHeight, n, f);

	m_Device->SetTransform(D3DTS_PROJECTION, &projection);
}

void MyD3DRenderer::CalculateOrthoMatrix(float n, float f)
{
	if(!m_Device) return;
	D3DXMATRIX ortho;

	D3DXMatrixOrthoLH(&ortho, (float)m_screenWidth, (float)m_screenHeight, n, f);
	m_Device->SetTransform(D3DTS_PROJECTION, &ortho);
}

void MyD3DRenderer::SetClearCol(float r, float g, float b)
{
	m_Color = D3DCOLOR_COLORVALUE(r,g,b,1.0f);
}

void MyD3DRenderer::StartRender(bool bColor, bool bDepth, bool bStencil)
{
	if(!m_Device) return;

	unsigned int buffers = 0;
	if(bColor) buffers |= D3DCLEAR_TARGET;
	if(bDepth) buffers |= D3DCLEAR_ZBUFFER;
	if(bStencil) buffers |= D3DCLEAR_STENCIL;

	if(FAILED(m_Device->Clear(0,NULL,buffers,m_Color,1,0)))
		return;
	
	if(FAILED(m_Device->BeginScene())) return;

	m_renderingScene = true;
}	

void MyD3DRenderer::EndRendering()
{
	if(!m_Device) return;

	m_Device->EndScene();
	m_Device->Present(NULL,NULL,NULL,NULL);

	m_renderingScene = false;
}

void MyD3DRenderer::ClearBuffers(bool bColor, bool bDepth, bool bStencil)
{
	if(!m_Device) return;

	unsigned int buffers = 0;
	if(bColor) buffers |= D3DCLEAR_TARGET;
	if(bDepth) buffers |= D3DCLEAR_ZBUFFER;
	if(bStencil) buffers |= D3DCLEAR_STENCIL;

	if(m_renderingScene) m_Device->EndScene();
	if(FAILED(m_Device->Clear(0,NULL,buffers,m_Color,1,0)))
		return;

	if(m_renderingScene)
		if(FAILED(m_Device->BeginScene())) return;
}

int MyD3DRenderer::CreateStaticBuffer(VertexType vType, PrimType primType, 
	int totalVerts, int totalIndices,
	int stride, void **data, unsigned int *indices, int *staticId)
{
	void *ptr;
	int index = m_numStaticBuffers;

	if(!m_staticBufferList)
	{
		m_staticBufferList = new myD3DStaticBuffer[1];
		if(!m_staticBufferList) return RE_FAIL;
	}
	else
	{
		myD3DStaticBuffer *temp;
		temp = new myD3DStaticBuffer[m_numStaticBuffers+1];

		memcpy(temp,m_staticBufferList,
			sizeof(myD3DStaticBuffer) * m_numStaticBuffers);

		delete[] m_staticBufferList;
		m_staticBufferList = temp;
	}

	m_staticBufferList[index].numVerts = totalVerts;
	m_staticBufferList[index].numIndices = totalIndices;
	m_staticBufferList[index].primType = primType;
	m_staticBufferList[index].stride = stride;
	m_staticBufferList[index].fvf = CreateD3DFVF(vType);

	if(totalIndices > 0)
	{
		if(FAILED(m_Device->CreateIndexBuffer(sizeof(unsigned int) * totalIndices, 
			D3DUSAGE_WRITEONLY,D3DFMT_INDEX16,D3DPOOL_DEFAULT,
			&m_staticBufferList[index].ibPtr,NULL))) return RE_FAIL;

		if(FAILED(m_staticBufferList[index].ibPtr->Lock(0,0,(void**)&ptr,0))) return RE_FAIL;

		memcpy(ptr,indices, sizeof(unsigned int)*totalIndices);
		m_staticBufferList[index].ibPtr->Unlock();
	}
	else
	{
		m_staticBufferList[index].ibPtr = NULL;
	}

	if(FAILED(m_Device->CreateVertexBuffer(totalVerts * stride, D3DUSAGE_WRITEONLY, m_staticBufferList[index].fvf,
		D3DPOOL_DEFAULT, &m_staticBufferList[index].vbPtr,NULL)))
		return RE_FAIL;

	if(FAILED(m_staticBufferList[index].vbPtr->Lock(0,0,(void**)&ptr,0))) 
		return RE_FAIL;

	memcpy(ptr,data,totalVerts*stride);
	m_staticBufferList[index].vbPtr->Unlock();

	*staticId = m_numStaticBuffers;
	m_numStaticBuffers++;
	
	return RE_OK;
}

void MyD3DRenderer::Shutdown()
{
	ReleaseAllStaticBuffers();
	ReleaseAllXModels();

	for(unsigned int s = 0; s < m_numTextures; s++)
	{
		if(m_textureList[s].fileName)
		{
			delete[] m_textureList[s].fileName;
			m_textureList[s].fileName = NULL;
		}
		if(m_textureList[s].image)
		{
			m_textureList[s].image->Release();
			m_textureList[s].image = NULL;
		}
	}

	m_numTextures = 0;
	if(m_textureList) delete[] m_textureList;
	m_textureList = NULL;

	for(int s=0; s<m_totalFonts; s++)
	{
		if(m_fonts[s])
		{
			m_fonts[s]->Release();
			m_fonts[s] = NULL;
		}
	}
	m_totalFonts = 0;
	if(m_fonts) delete[] m_fonts;
	m_fonts = NULL;

	for(int s=0; s<m_totalGUIs; s++)
	{
		m_guiList[s].Shutdown();
	}
	m_totalGUIs = 0;
	if(m_guiList) delete[] m_guiList;
	m_guiList = NULL;
	if (m_skyVertexBuffer) {
		m_skyVertexBuffer->Release();
		delete m_skyVertexBuffer;
		m_skyVertexBuffer = 0;
	}
	for (int i = 0; i<5; i++)
	{
		if (m_skyTexture[i]) {
			m_skyTexture[i]->Release();
			delete m_skyTexture[i];
			m_skyTexture[i] = 0;
		}	
	}

	if(m_Device) m_Device->Release();
	if(m_Direct3D) m_Direct3D->Release();

	m_Device = NULL;
	m_Direct3D = NULL;
}

int MyD3DRenderer::RenderStaticBuffer(int staticId)
{
	if(staticId >= m_numStaticBuffers) return RE_FAIL;

	if(m_activeStaticBuffer != staticId)
	{
		if(m_staticBufferList[staticId].ibPtr != NULL)
			m_Device->SetIndices(m_staticBufferList[staticId].ibPtr);
		m_Device->SetStreamSource(0,m_staticBufferList[staticId].vbPtr,0,m_staticBufferList[staticId].stride);
		m_Device->SetFVF(m_staticBufferList[staticId].fvf);

		m_activeStaticBuffer = staticId;
	}

	if(m_staticBufferList[staticId].ibPtr != NULL)
	{
		switch(m_staticBufferList[staticId].primType)
		{
		case POINT_LIST:
			if(FAILED(m_Device->DrawPrimitive(D3DPT_POINTLIST,0,
				m_staticBufferList[staticId].numVerts)))
				return RE_FAIL;
			break;
		case TRIANGLE_LIST:
			if(FAILED(m_Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,0,
				0,m_staticBufferList[staticId].numVerts/3,
				0,m_staticBufferList[staticId].numIndices)))
				return RE_FAIL;
			break;
		case TRIANGLE_STRIP:
			if(FAILED(m_Device->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,0,
				0,m_staticBufferList[staticId].numVerts/2,
				0,m_staticBufferList[staticId].numIndices)))
				return RE_FAIL;
			break;
		case TRIANGLE_FAN:
			if(FAILED(m_Device->DrawIndexedPrimitive(D3DPT_TRIANGLEFAN,0,
				0,m_staticBufferList[staticId].numVerts/2,
				0,m_staticBufferList[staticId].numIndices)))
				return RE_FAIL;
			break;
		case LINE_LIST:
			if(FAILED(m_Device->DrawIndexedPrimitive(D3DPT_LINELIST,0,
				0,m_staticBufferList[staticId].numVerts/2,
				0,m_staticBufferList[staticId].numIndices)))
				return RE_FAIL;
			break;
		case LINE_STRIP:
			if(FAILED(m_Device->DrawIndexedPrimitive(D3DPT_LINESTRIP,0,
				0,m_staticBufferList[staticId].numVerts,
				0,m_staticBufferList[staticId].numIndices)))
				return RE_FAIL;
			break;
		default:
			return RE_FAIL;
		}
	}
	else
	{
		switch(m_staticBufferList[staticId].primType)
		{
		case POINT_LIST:
			if(FAILED(m_Device->DrawPrimitive(D3DPT_POINTLIST,0,
				m_staticBufferList[staticId].numVerts)))
				return RE_FAIL;
			break;
		case TRIANGLE_LIST:
			if(FAILED(m_Device->DrawPrimitive(D3DPT_TRIANGLELIST,0,
				(int)(m_staticBufferList[staticId].numVerts/3))))
				return RE_FAIL;
			break;
		case TRIANGLE_STRIP:
			if(FAILED(m_Device->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,
				(int)(m_staticBufferList[staticId].numVerts/2))))
				return RE_FAIL;
			break;
		case TRIANGLE_FAN:
			if(FAILED(m_Device->DrawPrimitive(D3DPT_TRIANGLEFAN,0,
				(int)(m_staticBufferList[staticId].numVerts/2))))
				return RE_FAIL;
			break;
		case LINE_LIST:
			if(FAILED(m_Device->DrawPrimitive(D3DPT_LINELIST,0,
				(int)(m_staticBufferList[staticId].numVerts/2))))
				return RE_FAIL;
			break;
		case LINE_STRIP:
			if(FAILED(m_Device->DrawPrimitive(D3DPT_LINESTRIP,0,
				(int)(m_staticBufferList[staticId].numVerts))))
				return RE_FAIL;
			break;
		default:
			return RE_FAIL;
		}
	}

	return RE_OK;
}

void MyD3DRenderer::SetMaterial(myMaterial *mat)
{
	if(!mat || !m_Device) return ;

	D3DMATERIAL9 m = { mat->diffuseR, mat->diffuseG,
		mat->diffuseB, mat->diffuseA,
		mat->ambientR, mat->ambientG,
		mat->ambientB, mat->ambientA,
		mat->specularR, mat->specularG,
		mat->specularB, mat->specularA,
		mat->emissiveR, mat->emissiveG,
		mat->emissiveB, mat->emissiveA,
		mat->power
	};

	m_Device->SetMaterial(&m);
}

void MyD3DRenderer::SetLight(myLight *light, int index)
{
	if(!light || !m_Device || index < 0) return;

	D3DLIGHT9 l;

	l.Ambient.a = light->ambientA;
	l.Ambient.r = light->ambientR;
	l.Ambient.g = light->ambientG;
	l.Ambient.b = light->ambientB;

	l.Attenuation0 = light->attenuation0;
	l.Attenuation1 = light->attenuation1;
	l.Attenuation2 = light->attenuation2;

	l.Diffuse.a = light->diffuseA;
	l.Diffuse.r = light->diffuseR;
	l.Diffuse.g = light->diffuseG;
	l.Diffuse.b = light->diffuseB;

	l.Direction.x = light->dirX;
	l.Direction.y = light->dirY;
	l.Direction.z = light->dirZ;

	l.Falloff = light->falloff;
	l.Phi = light->lightPhi;

	l.Position.x = light->posX;
	l.Position.y = light->posY;
	l.Position.z = light->posZ;

	l.Range = light->range;

	l.Specular.a = light->specularA;
	l.Specular.r = light->specularR;
	l.Specular.g = light->specularG;
	l.Specular.b = light->specularB;

	l.Theta = light->lightTheta;

	if(light->lightType == LIGHT_POINT) l.Type = D3DLIGHT_POINT;
	else if(light->lightType == LIGHT_SPOT) l.Type = D3DLIGHT_SPOT;
	else l.Type = D3DLIGHT_DIRECTIONAL;

	m_Device->SetLight(index,&l);
	m_Device->LightEnable(index,TRUE);
}

void MyD3DRenderer::DisabledLight(int index)
{
	if(!m_Device) return;
	m_Device->LightEnable(index,FALSE);
}

void MyD3DRenderer::SetTranspency(RenderState state, TransState src, TransState dst)
{
	if(!m_Device) return;

	if(state == TRANSPARENCY_NONE)
	{
		m_Device->SetRenderState(D3DRS_ALPHABLENDENABLE,false);
		return;
	}

	if(state == TRANSPARENCY_ENABLE)
	{
		m_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

		switch(src)
		{
		case TRANS_ZERO:
			m_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);
			break;
		case TRANS_ONE:
			m_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
			break;
		case TRANS_SRCCOLOR:
			m_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);
			break;
		case TRANS_INVSRCCOLOR:
			m_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_INVSRCCOLOR);
			break;
		case TRANS_SRCALPHA:
			m_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			break;
		case TRANS_INVSRCALPHA:
			m_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_INVSRCALPHA);
			break;
		case TRANS_DSTALPHA:
			m_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_DESTALPHA);
			break;
		case TRANS_INVDSTALPHA:
			m_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_INVDESTALPHA);
			break;
		case TRANS_DSTCOLOR:
			m_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_DESTCOLOR);
			break;
		case TRANS_INVDSTCOLOR:
			m_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_INVDESTCOLOR);
			break;
		case TRANS_SRCALPHASAT:
			m_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHASAT);
			break;
		case TRANS_BOTHSRCALPHA:
			m_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_BOTHSRCALPHA);
			break;
		case TRANS_INVBOTHSRCALPHA:
			m_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_BOTHINVSRCALPHA);
			break;
		case TRANS_BLENDFACTOR:
			m_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_BLENDFACTOR);
			break;
		case TRANS_INVBLENDFACTOR:
			m_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_INVBLENDFACTOR);
			break;
		default:
			m_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
			return;
			break;
		}

		switch(dst)
		{
		case TRANS_ZERO:
			m_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
			break;
		case TRANS_ONE:
			m_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			break;
		case TRANS_SRCCOLOR:
			m_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCCOLOR);
			break;
		case TRANS_INVSRCCOLOR:
			m_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
			break;
		case TRANS_SRCALPHA:
			m_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCALPHA);
			break;
		case TRANS_INVSRCALPHA:
			m_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			break;
		case TRANS_DSTALPHA:
			m_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_DESTALPHA);
			break;
		case TRANS_INVDSTALPHA:
			m_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVDESTALPHA);
			break;
		case TRANS_DSTCOLOR:
			m_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_DESTCOLOR);
			break;
		case TRANS_INVDSTCOLOR:
			m_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVDESTCOLOR);
			break;
		case TRANS_SRCALPHASAT:
			m_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCALPHASAT);
			break;
		case TRANS_BOTHSRCALPHA:
			m_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_BOTHSRCALPHA);
			break;
		case TRANS_INVBOTHSRCALPHA:
			m_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_BOTHINVSRCALPHA);
			break;
		case TRANS_BLENDFACTOR:
			m_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_BLENDFACTOR);
			break;
		case TRANS_INVBLENDFACTOR:
			m_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVBLENDFACTOR);
			break;
		default:
			m_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
			return;
			break;
		}
	}
}

int MyD3DRenderer::AddTexture2D(char *file, int *texId)
{
	if(!file || !m_Device) return RE_FAIL;

	int len = strlen(file);
	if(!len) return RE_FAIL;

	int index = m_numTextures;

	if(!m_textureList)
	{
		m_textureList = new myD3DTexture[1];
		if(!m_textureList) return RE_FAIL;
	}
	else
	{
		myD3DTexture *temp;
		temp = new myD3DTexture[m_numTextures + 1];
		memcpy(temp, m_textureList, sizeof(myD3DTexture)*m_numTextures);

		delete[] m_textureList;
		m_textureList = temp;
	}

	m_textureList[index].fileName = new char[len];
	memcpy(m_textureList[index].fileName, file, len);

	D3DCOLOR colorkey = 0xff000000;
	D3DXIMAGE_INFO info;

	if(D3DXCreateTextureFromFileEx(m_Device,file,0,0,0,0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT,
		D3DX_DEFAULT,colorkey,&info,NULL,
		&m_textureList[index].image) != D3D_OK) return false;

	m_textureList[index].width = info.Width;
	m_textureList[index].height = info.Height;

	*texId = m_numTextures;
	m_numTextures++;

	return RE_OK;
}

void MyD3DRenderer::SetTextureFilter(int index, int filter, int val)
{
	if(!m_Device || index < 0) return;

	D3DSAMPLERSTATETYPE fil = D3DSAMP_MINFILTER;
	int v = D3DTEXF_POINT;

	if(filter == MIN_FILTER) fil = D3DSAMP_MINFILTER;
	if(filter == MAG_FILTER) fil = D3DSAMP_MAGFILTER;
	if(filter == MIP_FILTER) fil = D3DSAMP_MIPFILTER;

	if(val == POINT_TYPE) v = D3DTEXF_POINT;
	if(val == LINEAR_TYPE) v = D3DTEXF_LINEAR;
	if(val == ANISOTROPIC_TYPE) v = D3DTEXF_ANISOTROPIC;

	m_Device->SetSamplerState(index,fil,v);
}

void MyD3DRenderer::SetMultiTexture()
{
	if(!m_Device) return;

	m_Device->SetTextureStageState(0,D3DTSS_TEXCOORDINDEX,0);
	m_Device->SetTextureStageState(0,D3DTSS_COLOROP,D3DTOP_MODULATE);
	m_Device->SetTextureStageState(0,D3DTSS_COLORARG1,D3DTA_TEXTURE);
	m_Device->SetTextureStageState(0,D3DTSS_COLORARG2,D3DTA_DIFFUSE);

	m_Device->SetTextureStageState(1,D3DTSS_TEXCOORDINDEX,1);
	m_Device->SetTextureStageState(1,D3DTSS_COLOROP,D3DTOP_MODULATE);
	m_Device->SetTextureStageState(1,D3DTSS_COLORARG1,D3DTA_TEXTURE);
	m_Device->SetTextureStageState(1,D3DTSS_COLORARG2,D3DTA_CURRENT);

}

void MyD3DRenderer::ApplyTexture(int index, int texId)
{
	if(!m_Device) return;

	if(index < 0 || texId < 0)
		m_Device->SetTexture(0,NULL);
	else
		m_Device->SetTexture(index, m_textureList[texId].image);
}

void MyD3DRenderer::SaveScreenShot(char *file)
{
	if(!file) return;

	LPDIRECT3DSURFACE9 surface = NULL;
	D3DDISPLAYMODE disp;

	m_Device->GetDisplayMode(0,&disp);
	m_Device->CreateOffscreenPlainSurface(disp.Width,disp.Height,
		D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT,&surface,NULL);
	m_Device->GetBackBuffer(0,0,D3DBACKBUFFER_TYPE_MONO,&surface);
	D3DXSaveSurfaceToFile(file, D3DXIFF_JPG, surface, NULL, NULL);

	if(surface != NULL) surface->Release();
	surface = NULL;
}

void MyD3DRenderer::EnablePointSprites(float size, float min, float a, float b, float c)
{
	if(!m_Device) return;

	m_Device->SetRenderState(D3DRS_POINTSPRITEENABLE,TRUE);
	m_Device->SetRenderState(D3DRS_POINTSCALEENABLE,TRUE);
	m_Device->SetRenderState(D3DRS_POINTSIZE,FtoDW(size));
	m_Device->SetRenderState(D3DRS_POINTSIZE_MIN,FtoDW(min));
	m_Device->SetRenderState(D3DRS_POINTSCALE_A,FtoDW(a));
	m_Device->SetRenderState(D3DRS_POINTSCALE_B,FtoDW(b));
	m_Device->SetRenderState(D3DRS_POINTSCALE_C,FtoDW(c));
}

void MyD3DRenderer::DisablePointSprites()
{
	m_Device->SetRenderState(D3DRS_POINTSPRITEENABLE,FALSE);
	m_Device->SetRenderState(D3DRS_POINTSCALEENABLE,FALSE);
}

bool MyD3DRenderer::AddGUIBackdrop(int guiId, char *fileName)
{
	if(guiId >= m_totalGUIs) return false;

	int texID = -1, staticID = -1;

	if(!AddTexture2D(fileName, &texID)) return false;

	unsigned long col = D3DCOLOR_XRGB(255,255,255);

	myGUIVertex obj[] =
	{
		{(float)m_screenWidth, 0, 0, 1, col, 1, 0},
		{(float)m_screenWidth, (float)m_screenHeight, 0, 1, col, 1, 1},
		{0, 0, 0, 1, col, 0, 0},
		{0, (float)m_screenHeight, 0, 1, col, 0, 1},
	};

	if(!CreateStaticBuffer(MY_FVF_GUI,TRIANGLE_STRIP,4,0,sizeof(myGUIVertex),(void**)&obj,NULL,&staticID)) return false;

	return m_guiList[guiId].AddBackdrop(texID, staticID);
}

bool MyD3DRenderer::AddGUIStaticText(int guiId, int id,
		char *text, int x, int y, unsigned long color,
		int fontID)
{
	if(guiId >= m_totalGUIs) return false;

	return m_guiList[guiId].AddStaticText(id, text, x, y, color, fontID);
}

bool MyD3DRenderer::AddGUIButton(int guiId, int id, int x, int y,
		char *up, char *over, char *down)
{
	if(guiId >= m_totalGUIs) return false;

	int upID = -1, overID = -1, downID = -1, staticID = -1;

	if(!AddTexture2D(up,&upID)) return false;
	if(!AddTexture2D(over,&overID)) return false;
	if(!AddTexture2D(down,&downID)) return false;

	unsigned long col = D3DCOLOR_XRGB(255,255,255);

	int w = m_textureList[upID].width;
	int h = m_textureList[upID].height;

	myGUIVertex obj[] =
	{
		{(float)(w+x), (float)(0+y), 0, 1, col, 1, 0},
		{(float)(w+x), (float)(h+y), 0, 1, col, 1, 1},
		{(float)(0+x), (float)(0+y), 0, 1, col, 0, 0},
		{(float)(0+x), (float)(h+y), 0, 1, col, 0, 1},
	};

	if(!CreateStaticBuffer(MY_FVF_GUI,TRIANGLE_STRIP,4,0,
		sizeof(myGUIVertex),(void**)&obj,NULL,
		&staticID)) return false;

	return m_guiList[guiId].AddButton(id,x,y,w,h,upID,overID,downID,staticID);

	return true;
}

void MyD3DRenderer::ProcessGUI(int guiId, bool LMBDown,
		int mouseX, int mouseY,
		void(*funcPtr)(int id, int state))
{
   if(guiId >= m_totalGUIs || !m_Device) return;

   MyGUISystem *gui = &m_guiList[guiId];
     
   myGUIControl *backDrop = gui->GetBackDrop();
   
   if(backDrop)
      {
		ApplyTexture(0,backDrop->m_upTex);
		RenderStaticBuffer(backDrop->m_listID);
		ApplyTexture(0,-1);
      }

   int status = MOUSE_BUTTON_UP;

   for(int i = 0; i < gui->GetTotalControls(); i++)
      {
         myGUIControl *pCnt = gui->GetGUIControl(i);
         if(!pCnt) continue;

         switch(pCnt->m_type)
            {
               case GAME_GUI_STATICTEXT:
				   DisplayText(pCnt->m_listID, pCnt->m_xPos,
					   pCnt->m_yPos, pCnt->m_color, pCnt->m_text);
                  break;

               case GAME_GUI_BUTTON:
                  status = MOUSE_BUTTON_UP;


                  m_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
                  m_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
                  m_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

                  if(mouseX > pCnt->m_xPos && mouseX < pCnt->m_xPos + pCnt->m_width &&
                     mouseY > pCnt->m_yPos && mouseY < pCnt->m_yPos + pCnt->m_height)
                     {
                        if(LMBDown) status = MOUSE_BUTTON_DOWN;
                        else status = MOUSE_BUTTON_OVER;
                     }

                  if(status == MOUSE_BUTTON_UP) ApplyTexture(0, pCnt->m_upTex);
                  if(status == MOUSE_BUTTON_OVER) ApplyTexture(0, pCnt->m_overTex);
                  if(status == MOUSE_BUTTON_DOWN) ApplyTexture(0, pCnt->m_downTex);

				  RenderStaticBuffer(pCnt->m_listID);                 

                  m_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
                  break;
            }

         if(funcPtr) funcPtr(pCnt->m_id, status);
      }
}

bool MyD3DRenderer::CreateText(char *font, int weight, bool italic, int size, int &id)
{
	if(!m_fonts)
	{
		m_fonts = new LPD3DXFONT[1];
		if(!m_fonts) return RE_FAIL;
	}
	else
	{
		LPD3DXFONT *temp;
		temp = new LPD3DXFONT[m_totalFonts + 1];

		memcpy(temp,m_fonts,sizeof(LPD3DXFONT)*m_totalFonts);

		delete[] m_fonts;
		m_fonts = temp;
	}

	if(FAILED(D3DXCreateFont(m_Device,size,0,weight,1,italic,
		0,0,0,0,font,&m_fonts[m_totalFonts]))) return false;
	id = m_totalFonts;
	m_totalFonts++;

	return true;
}

void MyD3DRenderer::DisplayText(int id, long x, long y, int r, int g, int b, char *text, ...)
{
	RECT FontPosition = {x,y,m_screenWidth,m_screenHeight};
	char message[1024];
	va_list argList;

	if(id>=m_totalFonts) return;

	va_start(argList,text);
	vsprintf(message,text,argList);
	va_end(argList);

	m_fonts[id]->DrawText(NULL,message,-1,&FontPosition,
		DT_SINGLELINE,D3DCOLOR_ARGB(255,r,g,b));
}

void MyD3DRenderer::DisplayText(int id, long x, long y, unsigned long color, char *text, ...)
{
	RECT FontPosition = {x,y,m_screenWidth,m_screenHeight};
	char message[1024];
	va_list argList;

	if(id>=m_totalFonts) return;

	va_start(argList,text);
	vsprintf(message,text,argList);
	va_end(argList);

	m_fonts[id]->DrawText(NULL,message,-1,&FontPosition,
		DT_SINGLELINE,color);
}

void MyD3DRenderer::EnableFog(float start, float end, UGP_FOG_TYPE type, 
	unsigned long color, bool rangeFog)
{
	if(!m_Device) return;

	D3DCAPS9 caps;
	m_Device->GetDeviceCaps(&caps);

	m_Device->SetRenderState(D3DRS_FOGENABLE,true);
	m_Device->SetRenderState(D3DRS_FOGCOLOR, color);

	m_Device->SetRenderState(D3DRS_FOGSTART, *(DWORD*)(&start));
	m_Device->SetRenderState(D3DRS_FOGEND,*(DWORD*)(&end));

	if(type == UGP_VERTEX_FOG)
		m_Device->SetRenderState(D3DRS_FOGVERTEXMODE,D3DFOG_LINEAR);
	else
		m_Device->SetRenderState(D3DRS_FOGTABLEMODE,D3DFOG_LINEAR);

	if(caps.RasterCaps & D3DPRASTERCAPS_FOGRANGE)
	{
		if(rangeFog)
			m_Device->SetRenderState(D3DRS_RANGEFOGENABLE,true);
		else
			m_Device->SetRenderState(D3DRS_RANGEFOGENABLE,false);
	}
}

void MyD3DRenderer::DisableFog()
{
	if(!m_Device) return;

	m_Device->SetRenderState(D3DRS_FOGENABLE, false);
}

void MyD3DRenderer::SetDetailMapping()
{
	if(!m_Device) return;

	m_Device->SetTextureStageState(0,D3DTSS_TEXCOORDINDEX,0);
	m_Device->SetTextureStageState(0,D3DTSS_COLOROP,D3DTOP_SELECTARG1);
	m_Device->SetTextureStageState(0,D3DTSS_COLORARG1,D3DTA_TEXTURE);
	m_Device->SetTextureStageState(0,D3DTSS_COLORARG2,D3DTA_DIFFUSE);

	m_Device->SetTextureStageState(1,D3DTSS_TEXCOORDINDEX,1);
	m_Device->SetTextureStageState(1,D3DTSS_COLOROP,D3DTOP_ADDSIGNED);
	m_Device->SetTextureStageState(1,D3DTSS_COLORARG1,D3DTA_TEXTURE);
	m_Device->SetTextureStageState(1,D3DTSS_COLORARG2,D3DTA_CURRENT);

}

int MyD3DRenderer::LoadXModel(char *file, int *xModelId)
{
	if(!file)
		return RE_FAIL;

	if(!m_xModels)
	{
		m_xModels = new MyXModel[1];
		if(!m_xModels) return RE_FAIL;
		m_xModels[0].SetDevice(m_Device);
	}
	else
	{
		MyXModel *temp;
		temp = new MyXModel[m_numXModels + 1];
		memcpy(temp,m_xModels,sizeof(MyXModel)*m_numXModels);
		delete[] m_xModels;
		m_xModels = temp;

		m_xModels[m_numXModels].SetDevice(m_Device);
	}

	if(!m_xModels[m_numXModels].LoadXFile(file))
		return RE_FAIL;

	*xModelId = m_numXModels;
	m_numXModels++;

	return RE_OK;
}

int MyD3DRenderer::LoadXModel(char *file, int xModelId)
{
	if(!file || xModelId < 0 || xModelId >= m_numXModels || !m_xModels) return RE_FAIL;

	m_xModels[xModelId].Shutdown();

	if(!m_xModels[xModelId].LoadXFile(file))
		return RE_FAIL;

	return RE_OK;
}

int MyD3DRenderer::RenderXModel(int xModelId)
{
	if(!m_xModels || xModelId >= m_numXModels || xModelId < 0)
		return RE_FAIL;

	m_Device->SetIndices(NULL);
	m_Device->SetStreamSource(0,NULL,0,0);
	m_Device->SetFVF(0);

	m_xModels[xModelId].Render();

	return RE_OK;
}

int MyD3DRenderer::ReleaseXModel(int xModelId)
{
	if(!m_xModels || xModelId >= m_numXModels || xModelId < 0)
		return RE_FAIL;

	m_xModels[xModelId].Shutdown();

	return RE_OK;
}

void MyD3DRenderer::ReleaseAllStaticBuffers()
{
	for(int s=0; s<m_numStaticBuffers; s++)
	{
		ReleaseStaticBuffer(s);
	}

	m_numStaticBuffers = 0;
	if(m_staticBufferList) delete[] m_staticBufferList;
	m_staticBufferList = NULL;
}

void MyD3DRenderer::ReleaseAllXModels()
{
	for(int s=0; s<m_numXModels; s++)
	{
		m_xModels[s].Shutdown();
	}

	m_numXModels = 0;
	if(m_xModels) delete[] m_xModels;
	m_xModels = NULL; 
}

int MyD3DRenderer::ReleaseStaticBuffer(int staticID)
{
	if(staticID < 0 || staticID >= m_numStaticBuffers || 
		!m_staticBufferList) return RE_FAIL;

	m_staticBufferList[staticID].fvf = 0;
	m_staticBufferList[staticID].numIndices = 0;
	m_staticBufferList[staticID].numVerts = 0;
	m_staticBufferList[staticID].stride = 0;

	if(m_staticBufferList[staticID].vbPtr)
	{
		m_staticBufferList[staticID].vbPtr->Release();
		m_staticBufferList[staticID].vbPtr = NULL;
	}
	if(m_staticBufferList[staticID].ibPtr)
	{
		m_staticBufferList[staticID].ibPtr->Release();
		m_staticBufferList[staticID].ibPtr = NULL;
	}

	return RE_OK;
}

void MyD3DRenderer::ApplyView(MyVector3 pos, MyVector3 view, MyVector3 up)
{
	if(!m_Device) return;

	D3DXVECTOR3 cameraPos(pos.x,pos.y,pos.z);
	D3DXVECTOR3 lookAtPos(view.x, view.y, view.z);
	D3DXVECTOR3 upDir(up.x,up.y,up.z);

	D3DXMATRIX mat;
	D3DXMatrixLookAtLH(&mat, &cameraPos, &lookAtPos, &upDir);

	m_Device->SetTransform(D3DTS_VIEW, &mat);
}

void MyD3DRenderer::SetWorldMatrix(MyMatrix4x4 *mat)
{
	if(!m_Device || !mat) return;

	m_Device->SetTransform(D3DTS_WORLD, (D3DXMATRIX*)mat->matrix);
}

void MyD3DRenderer::CameraToViewMatrix(MyCamera *cam, MyMatrix4x4 *mat)
{
	if(!cam || !mat) return;

	D3DXVECTOR3 cameraPos(cam->m_pos.x,cam->m_pos.y,cam->m_pos.z);
	D3DXVECTOR3 lookAtPos(cam->m_view.x,cam->m_view.y,cam->m_view.z);
	D3DXVECTOR3 upDir(cam->m_up.x,cam->m_up.y,cam->m_up.z);

	D3DXMATRIX view;
	D3DXMatrixLookAtLH(&view,&cameraPos,&lookAtPos,&upDir);

	mat->matrix[0] = view._11;
	mat->matrix[1] = view._12;
	mat->matrix[2] = view._13;
	mat->matrix[3] = view._14;

	mat->matrix[4] = view._21;
	mat->matrix[5] = view._22;
	mat->matrix[6] = view._23;
	mat->matrix[7] = view._24;

	mat->matrix[8] = view._31;
	mat->matrix[9] = view._32;
	mat->matrix[10] = view._33;
	mat->matrix[11] = view._34;

	mat->matrix[12] = view._41;
	mat->matrix[13] = view._42;
	mat->matrix[14] = view._43;
	mat->matrix[15] = view._44;
}

void MyD3DRenderer::GetProjectMatrix(MyMatrix4x4 *mat)
{
	if(!mat) return;

	mat->matrix[0] = m_projection._11;
	mat->matrix[1] = m_projection._12;
	mat->matrix[2] = m_projection._13;
	mat->matrix[3] = m_projection._14;

	mat->matrix[4] = m_projection._21;
	mat->matrix[5] = m_projection._22;
	mat->matrix[6] = m_projection._23;
	mat->matrix[7] = m_projection._24;

	mat->matrix[8] = m_projection._31;
	mat->matrix[9] = m_projection._32;
	mat->matrix[10] = m_projection._33;
	mat->matrix[11] = m_projection._34;

	mat->matrix[12] = m_projection._41;
	mat->matrix[13] = m_projection._42;
	mat->matrix[14] = m_projection._43;
	mat->matrix[15] = m_projection._44;
}

bool MyD3DRenderer::InitSkyBox(float Length) {
	m_Length = Length;

	//1.创建。创建顶点缓存
	m_Device->CreateVertexBuffer(20 * sizeof(mySkyBoxVertex), 0,
		D3DFVF_SKYBOX, D3DPOOL_MANAGED, &m_skyVertexBuffer, 0);

	//用一个结构体把顶点数据先准备好
	mySkyBoxVertex vertices[] =
	{
		//前面的四个顶点
		{ -m_Length / 2, 0.0f,    m_Length / 2, 0.0f, 1.0f, },
		{ -m_Length / 2, m_Length / 2,   m_Length / 2, 0.0f, 0.0f, },
		{ m_Length / 2, 0.0f,    m_Length / 2, 1.0f, 1.0f, },
		{ m_Length / 2, m_Length / 2,   m_Length / 2, 1.0f, 0.0f, },

		//背面的四个顶点
		{ m_Length / 2, 0.0f,   -m_Length / 2, 0.0f, 1.0f, },
		{ m_Length / 2, m_Length / 2,  -m_Length / 2, 0.0f, 0.0f, },
		{ -m_Length / 2, 0.0f,   -m_Length / 2, 1.0f, 1.0f, },
		{ -m_Length / 2, m_Length / 2,  -m_Length / 2, 1.0f, 0.0f, },

		//左面的四个顶点
		{ -m_Length / 2, 0.0f,   -m_Length / 2, 0.0f, 1.0f, },
		{ -m_Length / 2, m_Length / 2,  -m_Length / 2, 0.0f, 0.0f, },
		{ -m_Length / 2, 0.0f,    m_Length / 2, 1.0f, 1.0f, },
		{ -m_Length / 2, m_Length / 2,   m_Length / 2, 1.0f, 0.0f, },

		//右面的四个顶点
		{ m_Length / 2, 0.0f,   m_Length / 2, 0.0f, 1.0f, },
		{ m_Length / 2, m_Length / 2,  m_Length / 2, 0.0f, 0.0f, },
		{ m_Length / 2, 0.0f,  -m_Length / 2, 1.0f, 1.0f, },
		{ m_Length / 2, m_Length / 2, -m_Length / 2, 1.0f, 0.0f, },

		//上面的四个顶点
		{ m_Length / 2, m_Length / 2, -m_Length / 2, 1.0f, 0.0f, },
		{ m_Length / 2, m_Length / 2,  m_Length / 2, 1.0f, 1.0f, },
		{ -m_Length / 2, m_Length / 2, -m_Length / 2, 0.0f, 0.0f, },
		{ -m_Length / 2, m_Length / 2,  m_Length / 2, 0.0f, 1.0f, },

	};

	//准备填充顶点数据
	void* pVertices;
	//2.加锁
	m_skyVertexBuffer->Lock(0, 0, (void**)&pVertices, 0);
	//3.访问。把结构体中的数据直接拷到顶点缓冲区中
	memcpy(pVertices, vertices, sizeof(vertices));
	//4.解锁
	m_skyVertexBuffer->Unlock();

	return true;
}
bool MyD3DRenderer::LoadSkyTextureFromFile(char *pFrontTextureFile, 
	char *pBackTextureFile, 
	char *pLeftTextureFile, 
	char *pRightTextureFile, 
	char *pTopTextureFile) {
	//从文件加载五张纹理
	D3DXCreateTextureFromFile(m_Device, pFrontTextureFile, &m_skyTexture[0]);  //前面
	D3DXCreateTextureFromFile(m_Device, pBackTextureFile, &m_skyTexture[1]);  //后面
	D3DXCreateTextureFromFile(m_Device, pLeftTextureFile, &m_skyTexture[2]);  //左面
	D3DXCreateTextureFromFile(m_Device, pRightTextureFile, &m_skyTexture[3]);  //右面
	D3DXCreateTextureFromFile(m_Device, pTopTextureFile, &m_skyTexture[4]);  //上面	
	return true;

}
void MyD3DRenderer::RenderSkyBox(D3DXMATRIX *pMatWorld, bool bRenderFrame) {
	m_Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);  //将纹理颜色混合的第一个参数的颜色值用于输出
	m_Device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);   //纹理颜色混合的第一个参数的值就取纹理颜色值
	m_Device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
	m_Device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);

	//Alpha混合设置, 设置混合系数
	m_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	m_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_DESTALPHA);
	m_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVDESTALPHA);
	m_Device->SetTransform(D3DTS_WORLD, pMatWorld);  //设置世界矩阵
	m_Device->SetStreamSource(0, m_skyVertexBuffer, 0, sizeof(mySkyBoxVertex));    //把包含的几何体信息的顶点缓存和渲染流水线相关联  
	m_Device->SetFVF(D3DFVF_SKYBOX);  //设置FVF灵活顶点格式

										  //一个for循环，将5个面绘制出来
	for (int i = 0; i<5; i++)
	{
		m_Device->SetTexture(0, m_skyTexture[i]);
		m_Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * 4, 2);
	}

	//对是否渲染线框的处理代码
	if (bRenderFrame)  //如果要渲染出线框的话
	{
		m_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME); //把填充模式设为线框填充
																		 //一个for循环，将5个面的线框绘制出来
		for (int i = 0; i<5; i++)
		{
			m_Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * 4, 2);	//绘制顶点 
		}

		m_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);	//把填充模式调回实体填充
	}
}