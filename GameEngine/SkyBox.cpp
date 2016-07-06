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

//��Ⱦ��պУ���һ�������趨��պ�������󣬵ڶ�������ѡ���Ƿ���Ⱦ���߿�
void MySkyBox::RenderSkyBox(D3DXMATRIX *pMatWorld, bool bRenderFrame)
{
	m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);  //��������ɫ��ϵĵ�һ����������ɫֵ�������
	m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);   //������ɫ��ϵĵ�һ��������ֵ��ȡ������ɫֵ
	m_pd3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
	m_pd3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);

	m_pd3dDevice->SetTransform(D3DTS_WORLD, pMatWorld);  //�����������
	m_pd3dDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(SKYBOXVERTEX));    //�Ѱ����ļ�������Ϣ�Ķ��㻺�����Ⱦ��ˮ�������  
	m_pd3dDevice->SetFVF(D3DFVF_SKYBOX);  //����FVF�����ʽ

										  //һ��forѭ������5������Ƴ���
	for (int i = 0; i<5; i++)
	{
		m_pd3dDevice->SetTexture(0, m_pTexture[i]);
		m_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * 4, 2);
	}

	//���Ƿ���Ⱦ�߿�Ĵ������
	if (bRenderFrame)  //���Ҫ��Ⱦ���߿�Ļ�
	{
		m_pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME); //�����ģʽ��Ϊ�߿����
																		 //һ��forѭ������5������߿���Ƴ���
		for (int i = 0; i<5; i++)
		{
			m_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * 4, 2);	//���ƶ��� 
		}

		m_pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);	//�����ģʽ����ʵ�����
	}
}

//������պ�����
bool MySkyBox::LoadSkyTextureFromFile(std::vector<char *> skyName)
{
	//���ļ�������������
	D3DXCreateTextureFromFile(m_pd3dDevice, skyName[0], &m_pTexture[0]);  //ǰ��
	D3DXCreateTextureFromFile(m_pd3dDevice, skyName[1], &m_pTexture[1]);  //����
	D3DXCreateTextureFromFile(m_pd3dDevice, skyName[2], &m_pTexture[2]);  //����
	D3DXCreateTextureFromFile(m_pd3dDevice, skyName[3], &m_pTexture[3]);  //����
	D3DXCreateTextureFromFile(m_pd3dDevice, skyName[4], &m_pTexture[4]);  //����	
	return TRUE;
}

//��ʼ��
bool MySkyBox::InitSkyBox(float Length)
{
	m_Length = Length;

	//1.�������������㻺��
	m_pd3dDevice->CreateVertexBuffer(20 * sizeof(SKYBOXVERTEX), 0,
		D3DFVF_SKYBOX, D3DPOOL_MANAGED, &m_pVertexBuffer, 0);

	//��һ���ṹ��Ѷ���������׼����
	SKYBOXVERTEX vertices[] =
	{
		//ǰ����ĸ�����
		{ -m_Length / 2, 0.0f,    m_Length / 2, 0.0f, 1.0f, },
		{ -m_Length / 2, m_Length / 2,   m_Length / 2, 0.0f, 0.0f, },
		{ m_Length / 2, 0.0f,    m_Length / 2, 1.0f, 1.0f, },
		{ m_Length / 2, m_Length / 2,   m_Length / 2, 1.0f, 0.0f, },

		//������ĸ�����
		{ m_Length / 2, 0.0f,   -m_Length / 2, 0.0f, 1.0f, },
		{ m_Length / 2, m_Length / 2,  -m_Length / 2, 0.0f, 0.0f, },
		{ -m_Length / 2, 0.0f,   -m_Length / 2, 1.0f, 1.0f, },
		{ -m_Length / 2, m_Length / 2,  -m_Length / 2, 1.0f, 0.0f, },

		//������ĸ�����
		{ -m_Length / 2, 0.0f,   -m_Length / 2, 0.0f, 1.0f, },
		{ -m_Length / 2, m_Length / 2,  -m_Length / 2, 0.0f, 0.0f, },
		{ -m_Length / 2, 0.0f,    m_Length / 2, 1.0f, 1.0f, },
		{ -m_Length / 2, m_Length / 2,   m_Length / 2, 1.0f, 0.0f, },

		//������ĸ�����
		{ m_Length / 2, 0.0f,   m_Length / 2, 0.0f, 1.0f, },
		{ m_Length / 2, m_Length / 2,  m_Length / 2, 0.0f, 0.0f, },
		{ m_Length / 2, 0.0f,  -m_Length / 2, 1.0f, 1.0f, },
		{ m_Length / 2, m_Length / 2, -m_Length / 2, 1.0f, 0.0f, },

		//������ĸ�����
		{ m_Length / 2, m_Length / 2, -m_Length / 2, 1.0f, 0.0f, },
		{ m_Length / 2, m_Length / 2,  m_Length / 2, 1.0f, 1.0f, },
		{ -m_Length / 2, m_Length / 2, -m_Length / 2, 0.0f, 0.0f, },
		{ -m_Length / 2, m_Length / 2,  m_Length / 2, 0.0f, 1.0f, },

	};

	//׼����䶥������
	void* pVertices;
	//2.����
	m_pVertexBuffer->Lock(0, 0, (void**)&pVertices, 0);
	//3.���ʡ��ѽṹ���е�����ֱ�ӿ������㻺������
	memcpy(pVertices, vertices, sizeof(vertices));
	//4.����
	m_pVertexBuffer->Unlock();

	return TRUE;
}