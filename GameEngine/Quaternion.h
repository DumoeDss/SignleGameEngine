#pragma once

#include<math.h>
#include"Vector.h"
#include"MathDefines.h"


class MyQuaternion 
{
   public:
      MyQuaternion();
	   MyQuaternion(float xAxis, float yAxis,
	               float zAxis, float wAxis);

      void operator=(const MyQuaternion &q);
      MyQuaternion operator*(const MyQuaternion &q);
      MyQuaternion operator+(const MyQuaternion &q);

      void CreateQuatFromAxis(MyVector3 &a, float radians);

      float Length();
      void Normal();

      MyQuaternion Conjugate();
      MyQuaternion CrossProduct(const MyQuaternion &q);

	   void Rotatef(float amount, float xAxis,
	                float yAxis, float zAxis);
      void RotationRadiansf(double X, double Y, double Z);

	   void CreateMatrix(float *pMatrix);

      void Slerp(const MyQuaternion &q1, const MyQuaternion &q2, float t);

	   float w, x, y, z;
};
