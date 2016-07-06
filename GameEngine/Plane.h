#pragma once

#include"MathLibrary.h"

class MyPlane
{
   public:
      MyPlane();
      MyPlane(float A, float B, float C, float D);
      MyPlane(MyVector3 &n, float D);
	  //创建平面
      void CreatePlaneFromTri(MyVector3 &v1, MyVector3 &v2,
                              MyVector3 &v3);
	  //平面法向量
      void SetPlaneNormal(float A, float B, float C)
      {
         a = A; b = B; c = C;
      }
      void SetPlaneIntercept(float D) { d = D; }

      bool Intersect(MyPlane &p2, MyPlane &p3,
                     MyVector3 *intersectPoint);
      bool Intersect(MyPlane &pl, MyVector3 *intersectPoint);
      bool Intersect(MyPlane &pl, MyRay *intersect);
      bool Intersect(MyVector3 &p1, MyVector3 &p2, MyVector3 &p3);

      int ClassifyPolygon(MyPolygon &pol);
      int ClassifyPoint(MyVector3 &v);
      int ClassifyPoint(float x, float y, float z);

      void Lerp(MyPlane &p1, MyPlane &p2, float amount);

      float GetDistance(MyVector3 &v)
      {
         return a * v.x + b * v.y + c * v.z + d;
      }

      float GetDistance(float x, float y, float z)
      {
         return a * x + b * y + c * z + d;
      }

      float a, b, c, d;
};

