#pragma once

#include"Vector.h"
#include"Ray.h"
#include"Plane.h"
#include"MathDefines.h"


class MyPolygon
{
   public:
      MyPolygon() : m_flag(0) { }

      void SetFlag(unsigned int fl) { m_flag = fl; }
      unsigned int GetFlag() { return m_flag; }
      void Copy(MyPolygon &pol);

      void Clip(MyPlane &pl, MyPolygon *front, MyPolygon *back);
      
      bool Intersect(MyRay &ray, bool cull, float *dist);

      unsigned int m_flag;
      MyVector3 m_vertexList[3];
};

