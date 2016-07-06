#pragma once
//����ϵͳ
#include "d3dx9.h"
#include "Defines.h"
#include <vector>

//���ӵ�F����ṹ
struct POINTVERTEX
{
	float x, y, z;    //����λ��
	float u, v;		  //������������
};
#define D3DFVF_POINTVERTEX (D3DFVF_XYZ|D3DFVF_TEX1)

struct  MYPARTICLE
{
	//����λ��
	float x, y, z; 
	//����������Y����ת�Ƕ�
	float RotationY; 
	//����������X����ת�Ƕ�
	float RotationX;
	//�����½��ٶ�
	float FallSpeed;    
	//������ת�ٶ�
	float RotationSpeed;
	//����������
	int   TextureIndex;     
};

class MyParticleClass
{
private:
	LPDIRECT3DDEVICE9 m_pd3dDevice;
	std::vector<MYPARTICLE> m_vParticle;
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer; //���Ӷ��㻺��
	std::vector<LPDIRECT3DTEXTURE9> m_vTextures; //������������
	std::vector<char *> m_vParName;	//���������ļ�������
	int m_ParticleNum;
	int m_ParticleLengh;
	int m_ParticleWidth;
	int m_ParticleHeight;

public:
	MyParticleClass(LPDIRECT3DDEVICE9 pd3dDevice, std::vector<char *> particleNames);
	~MyParticleClass();
	void Shutdown();
	HRESULT InitParticle(int num, int lengh, int width, int height);        //����ϵͳ��ʼ������
	HRESULT RenderParticle(float fElapsedTime);   //����ϵͳ��Ⱦ����
};

#include "Camera.h"
#include <list>

struct BoundingBox
{
	BoundingBox() {
		m_min = D3DXVECTOR3(0, 0, 0);
		m_max = D3DXVECTOR3(0, 0, 0);
	}

	bool isPointInside(D3DXVECTOR3& p);

	D3DXVECTOR3 m_min;
	D3DXVECTOR3 m_max;
};

	struct Particle
	{
		D3DXVECTOR3 m_position;
		D3DCOLOR    m_color;
		static const DWORD FVF;
	};

	struct Attribute
	{
		Attribute()
		{
			m_lifeTime = 0.0f;
			m_age = 0.0f;
			m_isAlive = true;
		}

		D3DXVECTOR3 m_position;
		D3DXVECTOR3 m_velocity;
		D3DXVECTOR3 m_acceleration;
		float       m_lifeTime;     
		float       m_age;           
		D3DXCOLOR   m_color;          
		D3DXCOLOR   m_colorFade;    
		bool        m_isAlive;
	};


	class MyParticleSystem
	{
	public:
		MyParticleSystem();
		virtual ~MyParticleSystem();

		virtual bool init(IDirect3DDevice9* device, char* texFileName);
		virtual void reset();
		
		virtual void resetParticle(Attribute* attribute) = 0;
		virtual void addParticle();

		virtual void update(float timeDelta) = 0;

		virtual void preRender();
		virtual void render();
		virtual void postRender();

		bool isEmpty();
		bool isDead();

	protected:
		virtual void removeDeadParticles();

	protected:
		IDirect3DDevice9*       m_device;
		D3DXVECTOR3             m_origin;
		BoundingBox        m_boundingBox;
		float                   m_emitRate;   
		float                   m_size;       
		IDirect3DTexture9*      m_texture;
		IDirect3DVertexBuffer9* m_vertexBuffer;
		std::list<Attribute>    m_particles;
		int                     m_maxParticles; 

		DWORD m_vbSize;      
		DWORD m_vbOffset;      
		DWORD m_vbBatchSize; 
	};


	class Snow : public MyParticleSystem
	{
	public:
		Snow(BoundingBox* boundingBox, int numParticles);
		void resetParticle(Attribute* attribute);
		void update(float timeDelta);
	};

	class Firework : public MyParticleSystem
	{
	public:
		Firework(D3DXVECTOR3* origin, int numParticles);
		void resetParticle(Attribute* attribute);
		void update(float timeDelta);
		void preRender();
		void postRender();
	};

	class ParticleGun : public MyParticleSystem
	{
	public:
		ParticleGun(MyCamera* camera);
		void resetParticle(Attribute* attribute);
		void update(float timeDelta);
	private:
		MyCamera* m_camera;
	};





float GetRandomFloat(float lowBound, float highBound);


void GetRandomVector(
	D3DXVECTOR3* out,
	D3DXVECTOR3* min,
	D3DXVECTOR3* max);

DWORD FtoDw(float f);
