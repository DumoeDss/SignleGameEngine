#include <stdio.h>
#include "D3DRender.h"
#include "Particle.h"
#include "SkyBox.h"
#include "Camera.h"
#include "Terrain.h"

inline unsigned long FtoDW(float v)
{
	return *((unsigned long *)&v);
}

#define D3DFVF_GUI (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define D3DFVF_MV (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
//创建渲染引擎对象
bool CreateD3DRender(MyD3DRender **pObj)
{
	if(!*pObj) 
		*pObj = new MyD3DRender();
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
	MultiSampleType ms, D3DDEVTYPE type, D3DFORMAT format, bool fullscreen)
{
	D3DMULTISAMPLE_TYPE t = D3DMULTISAMPLE_NONE;

	if(d3d)
	{
		switch(ms)
		{
		case D3DMULTISAMPLE_NONE:
			t = D3DMULTISAMPLE_NONE;
			break;
		case MY_MS_SAMPLES_2:
			if(d3d->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT,
				type,format,!fullscreen,D3DMULTISAMPLE_2_SAMPLES,
				NULL) == D3D_OK) t = D3DMULTISAMPLE_2_SAMPLES;
			break;
		case MY_MS_SAMPLES_4:
			if(d3d->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT,
				type,format,!fullscreen,D3DMULTISAMPLE_4_SAMPLES,
				NULL) == D3D_OK) t = D3DMULTISAMPLE_4_SAMPLES;
			break;
		case MY_MS_SAMPLES_8:
			if(d3d->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT,
				type,format,!fullscreen,D3DMULTISAMPLE_8_SAMPLES,
				NULL) == D3D_OK) t = D3DMULTISAMPLE_8_SAMPLES;
			break;
		case MY_MS_SAMPLES_16:
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

MyD3DRender::MyD3DRender() : m_screenWidth(0),
	m_screenHeight(0), m_near(0), m_far(0), m_Direct3D(0)
{
	m_Device = 0;
	m_renderingScene = false;
	m_numStaticBuffers = 0;
	m_activeStaticBuffer = RE_INVALID;
	m_staticBufferList = 0;
	m_terrain = 0;

	m_engineLog = 0;
	m_textureList = 0;
	m_numTextures = 0;
	m_totalFonts = 0;
	m_guiList = 0;
	m_totalGUIs = 0;
	m_fonts = 0;
//	m_xModels = 0;
	m_xModelAnim = 0;
	m_numXModels = 0;
	m_skyBox = 0;
	m_particle = 0;
	m_engineLog = 0;
}

MyD3DRender::~MyD3DRender()
{
	Shutdown();
}

bool MyD3DRender::InitRender(int w, int h, WinHWND mainWin, 
	bool fullScreen, MultiSampleType ms)
{
	//释放资源
	Shutdown();
	m_engineLog = new MyLogSystem("GameLog.log");
	m_mainHandle = mainWin;
	if(!m_mainHandle) return false;

	m_fullscreen = fullScreen;
	//创建D3D对象，D3D设备对象
	D3DDISPLAYMODE mode;
	D3DCAPS9 caps;
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	m_Direct3D = Direct3DCreate9(D3D_SDK_VERSION);
	if(!m_Direct3D) 
		return false;
	if(FAILED(m_Direct3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&mode))) 
		return false;
	if(FAILED(m_Direct3D->GetDeviceCaps(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,&caps))) 
		return false;
	DWORD processing = 0;
	if(caps.VertexProcessingCaps != 0)
		processing = D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE;
	else
		processing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	if(m_fullscreen)
	{
		d3dpp.FullScreen_RefreshRateInHz = mode.RefreshRate;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	}
	else
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	d3dpp.Windowed = !m_fullscreen;
	d3dpp.BackBufferWidth = w;
	d3dpp.BackBufferHeight = h;
	d3dpp.hDeviceWindow = m_mainHandle;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.MultiSampleType = GetD3DMultiSampleType(m_Direct3D,ms,D3DDEVTYPE_HAL,mode.Format,m_fullscreen);
	m_screenWidth = w;
	m_screenHeight = h;
	if (FAILED(m_Direct3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, 
		m_mainHandle, processing, &d3dpp, &m_Device))) {
		m_engineLog->AppendLog("[错误：]创建D3D设备失败.");
		return false;
	}		
	if(m_Device == 0)
		return false;
	OneTimeInit();
	return true;
}

LPDIRECT3DDEVICE9 MyD3DRender::GetDevice() {
	return m_Device;
}

void MyD3DRender::OneTimeInit()
{
	if(!m_Device) 
		return;
	CalculateProjMatrix(D3DX_PI/4, 0.1f, 200000.0f);
}
//透视投影
void MyD3DRender::CalculateProjMatrix(float fov,float n, float f)
{
	if(!m_Device) 
		return;
	D3DXMATRIX projection;

	D3DXMatrixPerspectiveFovLH(&projection, fov, (float)m_screenWidth/(float)m_screenHeight, n, f);

	m_Device->SetTransform(D3DTS_PROJECTION, &projection);
}
//正交投影
void MyD3DRender::CalculateOrthoMatrix(float n, float f)
{
	if(!m_Device) return;
	D3DXMATRIX ortho;

	D3DXMatrixOrthoLH(&ortho, (float)m_screenWidth, (float)m_screenHeight, n, f);
	m_Device->SetTransform(D3DTS_PROJECTION, &ortho);
}

void MyD3DRender::SetClearCol(float r, float g, float b)
{
	m_Color = D3DCOLOR_XRGB((int)r, (int)g, (int)b);
}

void MyD3DRender::StartRender(bool bColor, bool bDepth, bool bStencil)
{
	if(!m_Device) 
		return;

	unsigned int buffers = 0;
	if(bColor) buffers |= D3DCLEAR_TARGET;
	if(bDepth) buffers |= D3DCLEAR_ZBUFFER;
	if(bStencil) buffers |= D3DCLEAR_STENCIL;

	if (FAILED(m_Device->Clear(0, NULL, buffers, m_Color, 1.0f, 0))) {
		m_engineLog->AppendLog("[错误：]清屏失败.-- MyD3DRender::StartRender()");
		return;
	}
	
	if(FAILED(m_Device->BeginScene())) {
		m_engineLog->AppendLog("[错误：]开始渲染失败.-- MyD3DRender::StartRender()");
		return;
	}

	m_renderingScene = true;
}	

void MyD3DRender::EndRendering()
{
	if(!m_Device) return;

	m_Device->EndScene();
	m_Device->Present(NULL,NULL,NULL,NULL);

	m_renderingScene = false;
}

void MyD3DRender::ClearBuffers(bool bColor, bool bDepth, bool bStencil)
{
	if(!m_Device) return;

	unsigned int buffers = 0;
	if(bColor) buffers |= D3DCLEAR_TARGET;
	if(bDepth) buffers |= D3DCLEAR_ZBUFFER;
	if(bStencil) buffers |= D3DCLEAR_STENCIL;

	if(m_renderingScene) 
		m_Device->EndScene();
	if(FAILED(m_Device->Clear(0,NULL,buffers,m_Color,1,0))) {
		m_engineLog->AppendLog("[错误：]清屏失败.-- MyD3DRender::ClearBuffers()");
		return;
	}

	if(m_renderingScene)
		if(FAILED(m_Device->BeginScene())) {
			m_engineLog->AppendLog("[错误：]清屏失败.-- MyD3DRender::ClearBuffers()");
			return;
		}
}

int MyD3DRender::CreateStaticBuffer(VertexType vType, PrimType primType, 
	int totalVerts, int totalIndices,
	int stride, void **data, unsigned int *indices, int *staticId)
{
	void *ptr;
	int index = m_numStaticBuffers;

	if(!m_staticBufferList)
	{
		m_staticBufferList = new myD3DStaticBuffer[1];
		if(!m_staticBufferList) 
			return RE_FAIL;
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

void MyD3DRender::Shutdown()
{
	/*ReleaseAllStaticBuffers();
	ReleaseAllXModels();*/

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

	if (m_particle) {
		m_particle->Shutdown();
	}

	SAFE_DELETE(m_engineLog);

	SAFE_DELETE(m_skyBox);
	SAFE_DELETE(m_terrain);

	if(m_Device) m_Device->Release();
	if(m_Direct3D) m_Direct3D->Release();

	m_Device = NULL;
	m_Direct3D = NULL;
}

int MyD3DRender::RenderStaticBuffer(int staticId)
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

void MyD3DRender::SetMaterial(myMaterial *mat)
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

void MyD3DRender::SetLight(myLight *light, int index)
{
	if(!light || !m_Device || index < 0) return;

	D3DLIGHT9 l;

	l.Direction.x = light->dirX;
	l.Direction.y = light->dirY;
	l.Direction.z = light->dirZ;

	l.Position.x = light->posX;
	l.Position.y = light->posY;
	l.Position.z = light->posZ;

	if (light->lightType == LIGHT_POINT) {
		l.Type = D3DLIGHT_POINT;
		l.Ambient = light->color*0.6f;
		l.Diffuse = light->color;
		l.Specular = light->color*0.6f;
		l.Falloff = 1.0f;
		l.Range = 1000.0f;
		l.Attenuation0 = 1.0f;
		l.Attenuation1 = 0.0f;
		l.Attenuation2 = 0.0f;
	}
		
	else if (light->lightType == LIGHT_SPOT) {
		l.Type = D3DLIGHT_SPOT;
		l.Ambient = light->color*0.0f;
		l.Diffuse = light->color;
		l.Specular = light->color*0.6f;
		l.Falloff = 1.0f;
		l.Range = 1000.0f;
		l.Attenuation0 = 1.0f;
		l.Attenuation1 = 0.0f;
		l.Attenuation2 = 0.0f;
		l.Theta = 0.4f;
		l.Phi = 0.9f;
	}
		
	else {
		l.Type = D3DLIGHT_DIRECTIONAL;
		l.Ambient = light->color * 0.6f;
		l.Diffuse = light->color;
		l.Specular = light->color * 0.6f;
	}

	m_Device->SetLight(index,&l);
	m_Device->LightEnable(index,TRUE);
}

void MyD3DRender::DisabledLight(int index)
{
	if(!m_Device) return;
	m_Device->LightEnable(index,FALSE);
}

void MyD3DRender::SetTranspency(RenderState state, TransState src, TransState dst)
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

int MyD3DRender::AddTexture2D(char *file, int *texId)
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

	if (D3DXCreateTextureFromFileEx(m_Device, file, 0, 0, 0, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT,
		D3DX_DEFAULT, colorkey, &info, NULL,
		&m_textureList[index].image) != D3D_OK) {
		m_engineLog->AppendLog("[错误：]创建纹理贴图失败.-- MyD3DRender::AddTexture2D()");
		return false;
	}

	m_textureList[index].width = info.Width;
	m_textureList[index].height = info.Height;

	*texId = m_numTextures;
	m_numTextures++;

	return RE_OK;
}

void MyD3DRender::SetTextureFilter(int index, int filter, int val)
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

void MyD3DRender::SetMultiTexture()
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

void MyD3DRender::ApplyTexture(int index, int texId)
{
	if(!m_Device) return;

	if(index < 0 || texId < 0)
		m_Device->SetTexture(0,NULL);
	else
		m_Device->SetTexture(index, m_textureList[texId].image);
}

void MyD3DRender::SaveScreenShot(char *file)
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

void MyD3DRender::EnablePointSprites(float size, float min, float a, float b, float c)
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

void MyD3DRender::DisablePointSprites()
{
	m_Device->SetRenderState(D3DRS_POINTSPRITEENABLE,FALSE);
	m_Device->SetRenderState(D3DRS_POINTSCALEENABLE,FALSE);
}

bool MyD3DRender::AddGUIBackdrop(int guiId, char *fileName)
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

bool MyD3DRender::AddGUIStaticText(int guiId, int id,
		char *text, int x, int y, unsigned long color,
		int fontID)
{
	if(guiId >= m_totalGUIs) return false;

	return m_guiList[guiId].AddStaticText(id, text, x, y, color, fontID);
}

bool MyD3DRender::AddGUIButton(int guiId, int id, int x, int y,
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

//删除按钮
bool MyD3DRender::DelGUIButton(int guiId, int id) {
	m_guiList[guiId].DelButton(id);
	return true;
}
//删除静态文本
bool MyD3DRender::DelGUIStaticText(int guiId, int id) {
	m_guiList[guiId].DelStaticText(id);
	return true;
}

void MyD3DRender::ProcessGUI(int guiId, bool LMBDown,
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

                  if(status == MOUSE_BUTTON_UP) 
					  ApplyTexture(0, pCnt->m_upTex);
                  if(status == MOUSE_BUTTON_OVER) 
					  ApplyTexture(0, pCnt->m_overTex);
                  if(status == MOUSE_BUTTON_DOWN) 
					  ApplyTexture(0, pCnt->m_downTex);

				  RenderStaticBuffer(pCnt->m_listID);                 

                  m_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
                  break;
            }

         if(funcPtr) funcPtr(pCnt->m_id, status);
      }
}

bool MyD3DRender::CreateText(char *font, int weight, bool italic, int size, int &id)
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
		0,0,0,0,font,&m_fonts[m_totalFonts]))) {
		m_engineLog->AppendLog("[错误：]创建字体失败.-- MyD3DRender::CreateText()");
		return false;
	}
	id = m_totalFonts;
	m_totalFonts++;

	return true;
}

void MyD3DRender::DisplayText(int id, long x, long y, int r, int g, int b, char *text, ...)
{
	RECT FontPosition = {x,y,m_screenWidth,m_screenHeight};
	char message[1024];
	va_list argList;

	if(id>=m_totalFonts) return;

	va_start(argList,text);
	vsprintf(message, text, argList);
	va_end(argList);

	m_fonts[id]->DrawText(NULL,message,-1,&FontPosition,
		DT_SINGLELINE,D3DCOLOR_ARGB(255,r,g,b));
}

void MyD3DRender::DisplayText(int id, long x, long y, unsigned long color, char *text, ...)
{
	RECT fontPos = {x,y,m_screenWidth,m_screenHeight};
	char temp[1024];
	va_list textList;
	if(id>=m_totalFonts) return;
	va_start(textList,text);
	vsprintf(temp,text,textList);
	va_end(textList);
	m_fonts[id]->DrawText(NULL,temp,-1,&fontPos,
		DT_SINGLELINE,color);
}
//开启雾效
void MyD3DRender::EnableFog(float start, float end, FogType type, 
	unsigned long color, bool rangeFog)
{
	if(!m_Device) return;
	D3DCAPS9 caps;
	m_Device->GetDeviceCaps(&caps);
	m_Device->SetRenderState(D3DRS_FOGENABLE,true);
	m_Device->SetRenderState(D3DRS_FOGCOLOR, color);
	m_Device->SetRenderState(D3DRS_FOGSTART, *(DWORD*)(&start));
	m_Device->SetRenderState(D3DRS_FOGEND,*(DWORD*)(&end));
	if(type == FOG_VERTEX)
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
//关闭雾效
void MyD3DRender::DisableFog()
{
	if(!m_Device) return;

	m_Device->SetRenderState(D3DRS_FOGENABLE, false);
}

void MyD3DRender::SetDetailMapping()
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

//视图变化
void MyD3DRender::SetViewMatrix(MyMatrix4x4 *mat)
{
	if (!m_Device || !mat) return;

	m_Device->SetTransform(D3DTS_VIEW, (D3DXMATRIX*)mat->matrix);
}
//世界变化
void MyD3DRender::SetWorldMatrix(const MyMatrix4x4 *mat)
{
	if(!m_Device || !mat) return;

	m_Device->SetTransform(D3DTS_WORLD, (D3DXMATRIX*)mat->matrix);
}

void MyD3DRender::GetProjectMatrix(MyMatrix4x4 *mat)
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
//创建初始化粒子系统
void MyD3DRender::InitParticle(int type, int length, int width, int height,char* fileName,int numParticles, MyVector3 pos) {
	parType = type;
	if (type == 0)
	{
		BoundingBox boundingBox;
		
		boundingBox.m_min = D3DXVECTOR3(pos.x - width / 2.0f, 0, pos.z - length / 2.0f);
		boundingBox.m_max = D3DXVECTOR3(pos.x + width / 2.0f, pos.y, pos.z + length / 2.0f);
		m_parSystem = new Snow(&boundingBox, numParticles);
		m_parSystem->init(m_Device, fileName);
	}
	else if (type == 1)
	{
		D3DXVECTOR3 origin(pos.x, pos.y, pos.z);
		m_parSystem = new Firework(&origin, numParticles);
		m_parSystem->init(m_Device, fileName);
	}
	else if (type == 2)
	{
		/*m_parSystem = new ParticleGun(&m_Camera);
		m_parSystem->init(m_Device, fileName);*/
	}
}
//渲染粒子系统
bool MyD3DRender::RenderParticle(float fElapsedTime) {

	if (parType == 0)
	{
		m_parSystem->update(fElapsedTime);
	}
	else if (parType == 1)
	{
		m_parSystem->update(fElapsedTime);
		if (m_parSystem->isDead())
			m_parSystem->reset();
	}
	else if (parType == 2)
	{
		m_parSystem->update(fElapsedTime);
	}
	m_parSystem->render();
	//m_particle->RenderParticle(fElapsedTime);	
	return true;
}
//创建初始化天空盒
bool MyD3DRender::InitSkyBox(float skyLen, std::vector<char *> skyName) {
	m_skyBox = new MySkyBox(m_Device);	
	m_skyBox->LoadSkyTextureFromFile(skyName);
	m_skyBox->InitSkyBox(skyLen);
	return true;
}
//渲染天空盒
bool MyD3DRender::RenderSkyBox(D3DXMATRIX *pMatWorld, bool bRenderFrame) {
	m_skyBox->RenderSkyBox(pMatWorld, bRenderFrame);
	return true;
}
//创建初始化地形
bool MyD3DRender::InitTerrain(std::string heightmapFileName,
	int numVertsPerRow,
	int numVertsPerCol,
	int cellSpacing,
	float heightScale,
	std::string textureFileName) {
	m_terrain = new MyTerrain(m_Device,heightmapFileName, numVertsPerRow, numVertsPerCol, cellSpacing, heightScale);
	m_terrain->loadTexture(textureFileName);
	return true;
}
//渲染地形
void MyD3DRender::RenderTerrain(bool drawTris) {
	D3DXMATRIX I;
	D3DXMatrixIdentity(&I);
	m_terrain->renderTerrain(&I, drawTris);
}
//获取某一坐标地形高度
float MyD3DRender::getHeight(float x, float z) {
	return m_terrain->getHeight(x, z);
}

void MyD3DRender::InitObj(int type, MyVector3 pos, MyVector3 rot, MyVector3 scale, MyVector3 color) {
	m_objects.push_back(0);
	m_trans.push_back(D3DXMATRIX());
	D3DXMatrixTranslation(&m_trans.at(m_trans.size() - 1), pos.x, pos.y, pos.z);
	D3DXCOLOR col(D3DCOLOR_XRGB(static_cast<int>(color.x), static_cast<int>(color.y), static_cast<int>(color.z)));
	D3DMATERIAL9 mtrl;
	mtrl.Ambient = col;
	mtrl.Diffuse = col;
	mtrl.Specular = col;
	mtrl.Emissive = col;
	mtrl.Power = 2.0f;
	m_mtrls.push_back(mtrl);
	switch (type) {
	case 0://cube				
		D3DXCreateBox(m_Device, scale.x, scale.y, scale.z, &m_objects.at(m_objects.size()-1), 0);	
		break;
	case 1://sphere
		D3DXCreateSphere(m_Device, 1.0f, 20, 20, &m_objects.at(m_objects.size() - 1), 0);
		break;
	}
}

void MyD3DRender::RenderObj() {
	for (int i = 0; i != m_objects.size(); ++i) {
		m_Device->SetMaterial(&m_mtrls[i]);
		m_Device->SetTransform(D3DTS_WORLD, &m_trans[i]);
		m_objects[i]->DrawSubset(0);
	}
	
}

void MyD3DRender::SetXModelMatrix(int id, MyMatrix4x4& mat) {
	m_vecXModelAnim[id]->SetMatrix(mat);
}

void MyD3DRender::SetXModelScaleMatrix(int id, D3DXMATRIX& mat) {
	m_vecXModelAnim[id]->SetScaleMatrix(mat);
}

void MyD3DRender::UpdateXModelAnim(float fTimeDelta) {
	for (auto &xModel : m_vecXModelAnim) {
		xModel->UpdateXModel(fTimeDelta);
	}	
}

void MyD3DRender::RenderXModelAnim() {
	for (auto &xModel : m_vecXModelAnim) {
		//this->SetWorldMatrix(&xModel->GetMatrix());
		xModel->RenderXModel();
	}	
}

void MyD3DRender::AddXModel(char *name) {
	m_xModelAnim = new MyXModelAnim(m_Device);
	if (name == "") {
		return;
	}
	m_xModelAnim->InitXModel(name);
	m_vecXModelAnim.push_back(m_xModelAnim);
}

void MyD3DRender::DelXModel(int i) {
	m_vecXModelAnim.erase(m_vecXModelAnim.begin()+i);
}

void MyD3DRender::ChangeXModel(int i,char *name) {
	delete m_vecXModelAnim.at(i);
	m_xModelAnim = new MyXModelAnim(m_Device);
	m_xModelAnim->InitXModel(name);
	m_vecXModelAnim.at(i) = m_xModelAnim;
}