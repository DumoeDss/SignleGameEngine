#pragma once


#include<math.h>


class MyVector3
{
   public:
      MyVector3();
      MyVector3(float X, float Y, float Z);

      void operator=(MyVector3 &v);
      MyVector3 operator-(MyVector3 &v);
      MyVector3 operator+(MyVector3 &v);
      MyVector3 operator*(MyVector3 &v);
      MyVector3 operator/(MyVector3 &v);

      MyVector3 operator+(float f);
      MyVector3 operator-(float f);
      MyVector3 operator*(float f);
      MyVector3 operator/(float f);

      void operator +=(MyVector3 &v);
      void operator -=(MyVector3 &v);
      void operator *=(MyVector3 &v);
      void operator /=(MyVector3 &v);
      void operator +=(float f);
      void operator -=(float f);
      void operator *=(float f);
      void operator /=(float f);

      void CrossProduct(MyVector3 &v1, MyVector3 &v2);
      float DotProduct3(MyVector3 &v1);
      float GetLength();
      void Normal();
      void Normalize(MyVector3 &v1, MyVector3 &v2, MyVector3 &v3);

      float x, y, z;
};
