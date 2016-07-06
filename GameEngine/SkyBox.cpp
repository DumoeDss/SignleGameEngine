#include "SkyBox.h"
MySkyBox::MySkyBox(LPDIRECT3DDEVICE9  pDevice)
{
	m_pVertexBuffer = 0;
	m_pd3dDevice = pDevice;
	for (int i = 0; i<5; i++)
		m_pTexture[i] = 0;
	m_Length = 0.0f;
}

MySkyBox::~MySkyBox(void)
{
	Shutdown();
}

void MySkyBox::Shutdown() {
	SAFE_RELEASE(m_pVertexBuffer);
	for (int i = 0; i<5; i++)
	{
		SAFE_RELEASE(m_pTexture[i]);
	}
}

//渲染天空盒，第一个参数设定天空盒世界矩阵，第二个参数选择是否渲染出线框
void MySkyBox::RenderSkyBox(D3DXMATRIX *pMatWorld, bool bRenderFrame)
{
	m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);  //将纹理颜色混合的第一个参数的颜色值用于输出
	m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);   //纹理颜色混合的第一个参数的值就取纹理颜色值
	m_pd3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
	m_pd3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);

	m_pd3dDevice->SetTransform(D3DTS_WORLD, pMatWorld);  //设置世界矩阵
	m_pd3dDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(SKYBOXVERTEX));    //把包含的几何体信息的顶点缓存和渲染流水线相关联  
	m_pd3dDevice->SetFVF(D3DFVF_SKYBOX);  //设置FVF灵活顶点格式

										  //一个for循环，将5个面绘制出来
	for (int i = 0; i<5; i++)
	{
		m_pd3dDevice->SetTexture(0, m_pTexture[i]);
		m_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * 4, 2);
	}

	//对是否渲染线框的处理代码
	if (bRenderFrame)  //如果要渲染出线框的话
	{
		m_pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME); //把填充模式设为线框填充
																		 //一个for循环，将5个面的线框绘制出来
		for (int i = 0; i<5; i++)
		{
			m_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * 4, 2);	//绘制顶点 
		}

		m_pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);	//把填充模式调回实体填充
	}
}

//加载天空盒纹理
bool MySkyBox::LoadSkyTextureFromFile(std::vector<char *> skyName)
{
	//从文件加载五张纹理
	D3DXCreateTextureFromFile(m_pd3dDevice, skyName[0], &m_pTexture[0]);  //前面
	D3DXCreateTextureFromFile(m_pd3dDevice, skyName[1], &m_pTexture[1]);  //后面
	D3DXCreateTextureFromFile(m_pd3dDevice, skyName[2], &m_pTexture[2]);  //左面
	D3DXCreateTextureFromFile(m_pd3dDevice, skyName[3], &m_pTexture[3]);  //右面
	D3DXCreateTextureFromFile(m_pd3dDevice, skyName[4], &m_pTexture[4]);  //上面	
	return TRUE;
}

//初始化
bool MySkyBox::InitSkyBox(float Length)
{
	m_Length = Length;

	//1.创建。创建顶点缓存
	m_pd3dDevice->CreateVertexBuffer(20 * sizeof(SKYBOXVERTEX), 0,
		D3DFVF_SKYBOX, D3DPOOL_MANAGED, &m_pVertexBuffer, 0);

	//用一个结构体把顶点数据先准备好
	SKYBOXVERTEX vertices[] =
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
	m_pVertexBuffer->Lock(0, 0, (void**)&pVertices, 0);
	//3.访问。把结构体中的数据直接拷到顶点缓冲区中
	memcpy(pVertices, vertices, sizeof(vertices));
	//4.解锁
	m_pVertexBuffer->Unlock();

	return TRUE;
}