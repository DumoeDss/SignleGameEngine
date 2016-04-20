#include<math.h>
#include<stdlib.h>
#include"RainPS.h"

#define GET_RANDOM (((float)rand() - (float)rand()) / RAND_MAX)


MySnowPS::MySnowPS() : m_width(0), m_height(0), m_depth(0),
                     m_particles(0), m_maxParticles(0),
                     m_particleCount(0), m_totalTime(0)
{
   m_pos[0] = m_pos[1] = m_pos[2] = 0;
}


bool MySnowPS::Initialize(float x, float y, float z, int maxP,
                         float w, float h, float d)
{
   Shutdown();

   m_width = w; m_height = h; m_depth = d;
   m_particles = NULL;
   m_maxParticles = maxP;
   m_particleCount = 0;
   m_totalTime = 0;
   m_pos[0] = x; m_pos[1] = y; m_pos[2] = z;

   if(m_maxParticles <= 0) m_maxParticles = 1;
   
   m_particles = new MyParticle[m_maxParticles];
   if(!m_particles) return false;
   
   return true;
}


void MySnowPS::CreateParticle(int amount)
{
   for(int i = 0; i < amount; i++)
      {
         if(m_particleCount >= m_maxParticles) break;

         m_particles[m_particleCount].m_pos[0] = m_pos[0] +
            GET_RANDOM * m_width;
         m_particles[m_particleCount].m_pos[1] = m_height +
            GET_RANDOM * m_height;
         m_particles[m_particleCount].m_pos[2] = m_pos[2] +
            GET_RANDOM * m_depth;

         m_particles[m_particleCount].m_vel[0] = VEL_DIRX +
            GET_RANDOM * VEL_DELTAX;
         m_particles[m_particleCount].m_vel[1] = VEL_DIRY +
            GET_RANDOM * VEL_DELTAY;
         m_particles[m_particleCount].m_vel[2] = VEL_DIRZ +
            GET_RANDOM * VEL_DELTAZ;

         m_particleCount++;
      }
}


void MySnowPS::Update(float scalar)
{
   int numParticles = 0;
   
   for(int i = 0; i < m_particleCount;)
      {
         m_particles[i].m_pos[0] += m_particles[i].m_vel[0] * scalar;
         m_particles[i].m_pos[1] += m_particles[i].m_vel[1] * scalar;
         m_particles[i].m_pos[2] += m_particles[i].m_vel[2] * scalar;

         if(m_particles[i].m_pos[1] <= m_pos[1])
            {
               m_particleCount--;
               m_particles[i] = m_particles[m_particleCount];
            }
         else
            i++;
      }

   m_totalTime += scalar;
   numParticles = (int)(UPDATE_AMT * m_totalTime);
   if(m_totalTime > 1) m_totalTime = 0;
   
   CreateParticle(numParticles);
}


void MySnowPS::Shutdown()
{
   if(m_particles) delete[] m_particles;

   m_particles = NULL;
   m_particleCount = 0;
   m_totalTime = 0;
}