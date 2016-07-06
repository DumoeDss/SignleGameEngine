#include "Particle.h"

MyParticleClass::MyParticleClass(LPDIRECT3DDEVICE9 pd3dDevice, std::vector<char *> particleNames)
{
	m_pd3dDevice = pd3dDevice;
	m_pVertexBuffer = 0;
	m_vParName = particleNames;
	for (int i = 0; i != m_vParName.size(); ++i)
		m_vTextures.push_back(0);
}

MyParticleClass::~MyParticleClass()
{
	Shutdown();
}

void MyParticleClass::Shutdown() {
	SAFE_RELEASE(m_pVertexBuffer);
}

//初始化
HRESULT MyParticleClass::InitParticle(int num, int length, int width, int height)
{
	m_ParticleNum = num;
	m_ParticleLengh = length;
	m_ParticleWidth = width;
	m_ParticleHeight = height;
	for (int i = 0; i != num; ++i) {
		m_vParticle.push_back({ 0 });
	}
	//初始化雪花粒子数组
	srand(GetTickCount());
	for (auto &par : m_vParticle) {
		par.x = float(rand() % length - length / 2);
		par.y = float(rand() % width - width / 2);
		par.z = float(rand() % height);
		par.RotationX = (rand() % 100) / 50.0f*D3DX_PI;
		par.RotationY = (rand() % 100) / 50.0f*D3DX_PI;
		par.FallSpeed = 300.0f+rand() % 500;
		par.RotationSpeed = 5.0f + rand() % 10 / 10.0f;
		par.TextureIndex = rand() % m_vTextures.size();
	}
	//创建粒子顶点缓存
	m_pd3dDevice->CreateVertexBuffer(4 * sizeof(POINTVERTEX), 0,
		D3DFVF_POINTVERTEX, D3DPOOL_MANAGED, &m_pVertexBuffer, NULL);
	//填充粒子顶点缓存
	POINTVERTEX vertices[] =
	{
		{ -30.0f, 0.0f, 0.0f,   0.0f, 1.0f, },
		{ -30.0f, 60.0f, 0.0f,   0.0f, 0.0f, },
		{ 30.0f, 0.0f, 0.0f,   1.0f, 1.0f, },
		{ 30.0f, 60.0f, 0.0f,   1.0f, 0.0f, }
	};
	VOID* pVertices;
	m_pVertexBuffer->Lock(0, sizeof(vertices), (void**)&pVertices, 0);//加锁
	memcpy(pVertices, vertices, sizeof(vertices));//访问
	m_pVertexBuffer->Unlock();//解锁
	for (int i = 0; i != m_vParName.size(); ++i) {
		D3DXCreateTextureFromFile(m_pd3dDevice, m_vParName[i], &m_vTextures[i]);
	}
	return S_OK;
}

//渲染
HRESULT MyParticleClass::RenderParticle(float fElapsedTime)
{
	//更新每个雪花粒子的当前位置和角度
	for (auto &par : m_vParticle) {
		par.y -= par.FallSpeed*fElapsedTime;
		//如果粒子落到地面, 重新将其高度设置为最大
		if (par.y<0)
			par.y = m_ParticleWidth;
		//更改自旋角度
		par.RotationX += par.RotationSpeed * fElapsedTime;
		par.RotationY += par.RotationSpeed * fElapsedTime;
	}

	//禁用照明效果
	
	m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, false);

	//设置纹理状态
	m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);   //将纹理颜色混合的第一个参数的颜色值用于输出
	m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);   //纹理颜色混合的第一个参数的值就取纹理颜色值
	m_pd3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);  //缩小过滤状态采用线性纹理过滤
	m_pd3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR); //放大过滤状态采用线性纹理过滤

	//设置Alpha混合系数
	m_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);   //打开Alpha混合
	m_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);   //源混合系数设为1
	m_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);  //目标混合系数设为1																  
	m_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);	//设置剔出模式为不剔除任何面
	//渲染雪花
	for (int i = 0; i != m_vParticle.size(); ++i) {
		//构造并设置当前雪花粒子的世界矩阵
		static D3DXMATRIX matYaw, matPitch, matTrans, matWorld;
		D3DXMatrixRotationY(&matYaw, m_vParticle[i].RotationY);
		D3DXMatrixRotationX(&matPitch, m_vParticle[i].RotationX);
		D3DXMatrixTranslation(&matTrans, m_vParticle[i].x, m_vParticle[i].y, m_vParticle[i].z);
		matWorld = matYaw * matPitch * matTrans;
		m_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);

		//渲染当前雪花粒子
		m_pd3dDevice->SetTexture(0, m_vTextures[m_vParticle[i].TextureIndex]);    //设置纹理
		m_pd3dDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(POINTVERTEX));  //把包含的几何体信息的顶点缓存和渲染流水线相关联  
		m_pd3dDevice->SetFVF(D3DFVF_POINTVERTEX);    //设置FVF灵活顶点格式
		m_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);   //绘制
	}

	//恢复相关渲染状态：Alpha混合 、剔除状态、光照
	m_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	m_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, true);

	return S_OK;
}



#include <cstdlib>


bool BoundingBox::isPointInside(D3DXVECTOR3& p)
{
	if (p.x >= m_min.x && p.y >= m_min.y && p.z >= m_min.z &&
		p.x <= m_max.x && p.y <= m_max.y && p.z <= m_max.z)
	{
		return true;
	}
	else
	{
		return false;
	}
}

const DWORD Particle::FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;

MyParticleSystem::MyParticleSystem()
{
	m_device = 0;
	m_vertexBuffer = 0;
	m_texture = 0;
}

MyParticleSystem::~MyParticleSystem()
{
	SAFE_RELEASE(m_vertexBuffer);
	SAFE_RELEASE(m_texture);
}

bool MyParticleSystem::init(IDirect3DDevice9* device, char* texFileName)
{

	m_device = device; 

	HRESULT hr = 0;

	hr = device->CreateVertexBuffer(
		m_vbSize * sizeof(Particle),
		D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY,
		Particle::FVF,
		D3DPOOL_DEFAULT, 
		&m_vertexBuffer,
		0);

	if (FAILED(hr))
	{
		::MessageBox(0, "CreateVertexBuffer() - FAILED", "MyParticleSystem", 0);
		return false;
	}

	hr = D3DXCreateTextureFromFile(
		device,
		texFileName,
		&m_texture);

	if (FAILED(hr))
	{
		::MessageBox(0, "D3DXCreateTextureFromFile() - FAILED", "MyParticleSystem", 0);
		return false;
	}

	return true;
}

void MyParticleSystem::reset()
{
	std::list<Attribute>::iterator i;
	for (i = m_particles.begin(); i != m_particles.end(); i++)
	{
		resetParticle(&(*i));
	}
}

void MyParticleSystem::addParticle()
{
	Attribute attribute;

	resetParticle(&attribute);

	m_particles.push_back(attribute);
}

void MyParticleSystem::preRender()
{
	m_device->SetRenderState(D3DRS_LIGHTING, false);
	m_device->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
	m_device->SetRenderState(D3DRS_POINTSCALEENABLE, true);
	m_device->SetRenderState(D3DRS_POINTSIZE, FtoDw(m_size));
	m_device->SetRenderState(D3DRS_POINTSIZE_MIN, FtoDw(0.0f));

	m_device->SetRenderState(D3DRS_POINTSCALE_A, FtoDw(0.0f));
	m_device->SetRenderState(D3DRS_POINTSCALE_B, FtoDw(0.0f));
	m_device->SetRenderState(D3DRS_POINTSCALE_C, FtoDw(1.0f));

	m_device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

	m_device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	m_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

void MyParticleSystem::postRender()
{
	m_device->SetRenderState(D3DRS_LIGHTING, true);
	m_device->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
	m_device->SetRenderState(D3DRS_POINTSCALEENABLE, false);
	m_device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

void MyParticleSystem::render()
{
	if (!m_particles.empty())
	{

		preRender();

		m_device->SetTexture(0, m_texture);
		m_device->SetFVF(Particle::FVF);
		m_device->SetStreamSource(0, m_vertexBuffer, 0, sizeof(Particle));

		if (m_vbOffset >= m_vbSize)
			m_vbOffset = 0;

		Particle* v = 0;

		m_vertexBuffer->Lock(
			m_vbOffset * sizeof(Particle),
			m_vbBatchSize * sizeof(Particle),
			(void**)&v,
			m_vbOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

		DWORD numParticlesInBatch = 0;

		std::list<Attribute>::iterator i;
		for (i = m_particles.begin(); i != m_particles.end(); i++)
		{
			if (i->m_isAlive)
			{
				v->m_position = i->m_position;
				v->m_color = (D3DCOLOR)i->m_color;
				v++; 

				numParticlesInBatch++; 

				if (numParticlesInBatch == m_vbBatchSize)
				{
					m_vertexBuffer->Unlock();

					m_device->DrawPrimitive(
						D3DPT_POINTLIST,
						m_vbOffset,
						m_vbBatchSize);

					m_vbOffset += m_vbBatchSize;

					if (m_vbOffset >= m_vbSize)
						m_vbOffset = 0;

					m_vertexBuffer->Lock(
						m_vbOffset * sizeof(Particle),
						m_vbBatchSize * sizeof(Particle),
						(void**)&v,
						m_vbOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

					numParticlesInBatch = 0;
				}
			}
		}

		m_vertexBuffer->Unlock();

		if (numParticlesInBatch)
		{
			m_device->DrawPrimitive(
				D3DPT_POINTLIST,
				m_vbOffset,
				numParticlesInBatch);
		}

		m_vbOffset += m_vbBatchSize;

		postRender();
	}
}

bool MyParticleSystem::isEmpty()
{
	return m_particles.empty();
}

bool MyParticleSystem::isDead()
{
	std::list<Attribute>::iterator i;
	for (i = m_particles.begin(); i != m_particles.end(); i++)
	{
		if (i->m_isAlive)
			return false;
	}
	return true;
}

void MyParticleSystem::removeDeadParticles()
{
	std::list<Attribute>::iterator i;

	i = m_particles.begin();

	while (i != m_particles.end())
	{
		if (i->m_isAlive == false)
		{
			i = m_particles.erase(i);
		}
		else
		{
			i++;
		}
	}
}

Snow::Snow(BoundingBox* boundingBox, int numParticles)
{
	m_boundingBox = *boundingBox;
	m_size = 0.25f;
	m_vbSize = 2048;
	m_vbOffset = 0;
	m_vbBatchSize = 512;

	for (int i = 0; i < numParticles; i++)
		addParticle();
}

void Snow::resetParticle(Attribute* attribute)
{
	attribute->m_isAlive = true;

	GetRandomVector(
		&attribute->m_position,
		&m_boundingBox.m_min,
		&m_boundingBox.m_max);

	attribute->m_position.y = m_boundingBox.m_max.y;

	attribute->m_velocity.x = GetRandomFloat(0.0f, 1.0f) * -3.0f;
	attribute->m_velocity.y = GetRandomFloat(0.0f, 1.0f) * -10.0f;
	attribute->m_velocity.z = 0.0f;

	attribute->m_color = D3DCOLOR_XRGB(255, 255, 255);
}

void Snow::update(float timeDelta)
{
	std::list<Attribute>::iterator i;
	for (i = m_particles.begin(); i != m_particles.end(); i++)
	{
		i->m_position += i->m_velocity * timeDelta;

		if (m_boundingBox.isPointInside(i->m_position) == false)
		{
			resetParticle(&(*i));
		}
	}
}

Firework::Firework(D3DXVECTOR3* origin, int numParticles)
{
	m_origin = *origin;
	m_size = 0.9f;
	m_vbSize = 2048;
	m_vbOffset = 0;
	m_vbBatchSize = 512;

	for (int i = 0; i < numParticles; i++)
		addParticle();
}

void Firework::resetParticle(Attribute* attribute)
{
	attribute->m_isAlive = true;
	attribute->m_position = m_origin;

	D3DXVECTOR3 min = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);
	D3DXVECTOR3 max = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	GetRandomVector(
		&attribute->m_velocity,
		&min,
		&max);

	D3DXVec3Normalize(
		&attribute->m_velocity,
		&attribute->m_velocity);

	attribute->m_velocity *= 100.0f;

	attribute->m_color = D3DXCOLOR(
		GetRandomFloat(0.0f, 1.0f),
		GetRandomFloat(0.0f, 1.0f),
		GetRandomFloat(0.0f, 1.0f),
		1.0f);

	attribute->m_age = 0.0f;
	attribute->m_lifeTime = 2.0f; 
}

void Firework::update(float timeDelta)
{
	std::list<Attribute>::iterator i;

	for (i = m_particles.begin(); i != m_particles.end(); i++)
	{
		if (i->m_isAlive)
		{
			i->m_position += i->m_velocity * timeDelta;

			i->m_age += timeDelta;

			if (i->m_age > i->m_lifeTime)
				i->m_isAlive = false;
		}
	}
}

void Firework::preRender()
{
	MyParticleSystem::preRender();

	m_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	m_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	m_device->SetRenderState(D3DRS_ZWRITEENABLE, false);
}

void Firework::postRender()
{
	MyParticleSystem::postRender();

	m_device->SetRenderState(D3DRS_ZWRITEENABLE, true);
}

ParticleGun::ParticleGun(MyCamera* camera)
{
	m_camera = camera;
	m_size = 0.8f;
	m_vbSize = 2048;
	m_vbOffset = 0;
	m_vbBatchSize = 512;
}

void ParticleGun::resetParticle(Attribute* attribute)
{
	attribute->m_isAlive = true;

	D3DXVECTOR3 cameraPos;
	m_camera->getPosition(&cameraPos);

	D3DXVECTOR3 cameraDir;
	m_camera->getLook(&cameraDir);

	attribute->m_position = cameraPos;
	attribute->m_position.y -= 1.0f; 
	attribute->m_velocity = cameraDir * 100.0f;

	attribute->m_color = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);

	attribute->m_age = 0.0f;
	attribute->m_lifeTime = 1.0f; 
}

void ParticleGun::update(float timeDelta)
{
	std::list<Attribute>::iterator i;

	for (i = m_particles.begin(); i != m_particles.end(); i++)
	{
		i->m_position += i->m_velocity * timeDelta;

		i->m_age += timeDelta;

		if (i->m_age > i->m_lifeTime) 
			i->m_isAlive = false;
	}
	removeDeadParticles();
}

float GetRandomFloat(float lowBound, float highBound)
{
	if (lowBound >= highBound) 
		return lowBound;

	float f = (rand() % 10000) * 0.0001f;

	return (f * (highBound - lowBound)) + lowBound;
}

void GetRandomVector(
	D3DXVECTOR3* out,
	D3DXVECTOR3* min,
	D3DXVECTOR3* max)
{
	out->x = GetRandomFloat(min->x, max->x);
	out->y = GetRandomFloat(min->y, max->y);
	out->z = GetRandomFloat(min->z, max->z);
}

DWORD FtoDw(float f)
{
	return *((DWORD*)&f);
}

