#pragma once

#include"MathLibrary.h"


class MyRay
{
   public:
      MyRay(){}

      bool Intersect(MyVector3 &pos, float radius, float *dist);
      bool Intersect(MyVector3 &p1, MyVector3 &p2, MyVector3 &p3,
                     bool cull, float *dist);
      bool Intersect(MyVector3 &p1, MyVector3 &p2, MyVector3 &p3,
                     bool cull, float length, float *dist);
      bool Intersect(MyPlane &pl, bool cull,
                     MyVector3 *intersectPoint, float *dist);
      bool Intersect(MyPlane &pl, bool cull, float length,
                     MyVector3 *intersectPoint, float *dist);

      MyVector3 m_origin;
      MyVector3 m_direction;
};

