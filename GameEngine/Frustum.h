#pragma once

#define MAX_SIDES       6

#include"Plane.h"


class MyFrustum
{
   public:
      void CalculateFrustum(float *mv, float *proj);
      bool isPointVisiable(float x, float y, float z);
      bool isSphereVisiable(float x, float y, float z, float radius);
      bool isBoxVisiable(float x, float y, float z, float size);

   protected:
      void NormalizeFrustum();

   protected:
      MyPlane Frustum[MAX_SIDES];
};
