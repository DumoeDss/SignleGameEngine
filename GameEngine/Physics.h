#pragma once

#include"Vector.h"


struct myPointMass
{
   myPointMass() : m(0) {}
   float m;
   MyVector3 pos;
   MyVector3 velocity;
   MyVector3 force;
};


inline void ApplyForce(MyVector3 force, myPointMass *m)
{
   if(m != 0) m->force += force;
}


inline void SimulateMass(float dt, myPointMass *m)
{
   if(m != 0)
      {
         m->velocity += (m->force / m->m) * dt;
         m->pos += m->velocity * dt;
      }
}
