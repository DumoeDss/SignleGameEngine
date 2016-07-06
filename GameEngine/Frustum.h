#pragma once

#define MAX_SIDES       6

#include"Plane.h"
//视锥体
class MyFrustum
{
   public:
	   //计算视锥体
      void CalculateFrustum(float *mv, float *proj);
	  //判断是否可见
      bool isPointVisiable(float x, float y, float z);
      bool isSphereVisiable(float x, float y, float z, float radius);
      bool isBoxVisiable(float x, float y, float z, float size);

   protected:
      void NormalizeFrustum();

   protected:
      MyPlane Frustum[MAX_SIDES];
};
