#pragma once

#define VEL_DIRX 0.0f
#define VEL_DIRY -0.4f
#define VEL_DIRZ 0.0f

#define VEL_DELTAX 0.0f
#define VEL_DELTAY 0.1f
#define VEL_DELTAZ 0.0f

#define UPDATE_AMT 1000


class MyParticle
{
   public:
      MyParticle()
         {
            m_pos[0] = 0; m_pos[1] = 0; m_pos[2] = 0;
            m_vel[0] = 0; m_vel[1] = 0; m_vel[2] = 0;
         }
      
      float m_pos[3];
      float m_vel[3];
};


class MySnowPS
{
   public:
      MySnowPS();

      bool Initialize(float x, float y, float z, int maxP,
                      float w, float h, float d);

      void Update(float scalar);

      void CreateParticle(int amount);
      void Shutdown();

      float m_width;
      float m_height;
      float m_depth;

      float m_pos[3];
      MyParticle *m_particles;
      int m_maxParticles;
      int m_particleCount;
      float m_totalTime;
};
